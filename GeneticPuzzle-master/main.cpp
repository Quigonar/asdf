#include <SFML/Graphics.hpp>
#include <thread>

#include "UtilityProgram.h"
#include "Piece.h"

using namespace sf;
using namespace std;

vector <vector<int>> puzzleMap;
vector <int> tempMap;

Texture puzzleTexture;
List<Vector2f>* listPosImages = new List<sf::Vector2f>();
List<Vector2f>* listPosFitness = new List<sf::Vector2f>();
List<MatrixNode<int>*>* listFitness = new List<MatrixNode<int>*>();
List<int>* listMutations = new List<int>();
List<Matrix<int>*>* listGenerations = new List<Matrix<int>*>();

float dimensionX;
float dimensionY;
const int fps = 25;


/// Function that loads the images
/// \param image
/// \param numPieces
/// \param rows
/// \param cols
void loadImages(const string& image, int rows, int cols)
{
    //Load the texture of the image
    puzzleTexture.loadFromFile(image);

    //Get its dimensions
    dimensionX = puzzleTexture.getSize().x;
    dimensionY = puzzleTexture.getSize().y;

    float col = dimensionX / cols;
    float row = dimensionY / rows;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            listPosImages->addData(sf::Vector2f(i*row,j*col));
        }
    }
}
/// Function that load the position fitness of the images
/// \param matrix
void loadPosFitness(Matrix<int>* matrix)
{
    for(int i = 0; i < matrix->getRows(); i++)
    {
        for(int j = 0; j < matrix->getCols(); j++)
        {
            listPosFitness->addData(sf::Vector2f(i,j));
        }
    }
}

/// Function that sorts the list of fitness
/// \param list
void sortFitness(List<MatrixNode<int>*>* list)
{
    MatrixNode<int> *tempData;
    Node<MatrixNode<int>*> *auxNode = list->getHead();
    Node<MatrixNode<int>*> *temp = auxNode;

    while(auxNode)
    {
        temp = auxNode;
        while(temp->next)
        {
            temp = temp->next;

            if(auxNode->data->getH() < temp->data->getH())
            {
                tempData = auxNode->data;
                auxNode->data = temp->data;
                temp->data = tempData;
            }
        }
        auxNode = auxNode->next;
    }
}

/// Function that calculates the fitness of each individual
/// \param matrix
void loadFitness(Matrix<int>* matrix)
{
    int position;
    int xEnd;
    int yEnd;

    for(int i = 0 ; i < matrix->getRows(); i++)
    {
        for(int j = 0; j < matrix->getCols(); j++)
        {
            MatrixNode<int>* node = matrix->getNodePos(i,j);
            position = node->getData();
            xEnd = listPosFitness->getDataPos(position).x;
            yEnd = listPosFitness->getDataPos(position).y;
            node->setH(abs(xEnd - i) + abs(yEnd - j));
            listFitness->addData(node);
        }
    }
    sortFitness(listFitness);
}

/// Function that changes the position of the selected individuals
/// \param matrix
/// \param list
/// \return
Matrix<int>* crossover(Matrix<int>* matrix, List<MatrixNode<int>*>* list)
{
    int position1 = matrix->getNodeData(matrix,list->getDataPos(0)->getData())->getData();
    int position2 = matrix->getNodeData(matrix,list->getDataPos(1)->getData())->getData();
    int position3 = matrix->getNodeData(matrix,list->getDataPos(2)->getData())->getData();

    matrix->getNodeData(matrix,list->getDataPos(0)->getData())->setData(position3);
    matrix->getNodeData(matrix,list->getDataPos(1)->getData())->setData(position1);
    matrix->getNodeData(matrix,list->getDataPos(2)->getData())->setData(position2);

    return matrix;
}

/// Function that mutates an individual
/// \param numPieces
/// \param matrix
void mutation(int numPieces, Matrix<int>* matrix)
{
    int mutation;
    srand(time(NULL));
    mutation = (rand() % 100);

    if(mutation <= 30)
    {
        //Mutate
        int number1;
        int number2;
        bool done = false;

        while(!done)
        {
            srand(time(NULL));
            number1 =(rand() % numPieces);
            srand(time(NULL));
            number2 =(rand() % numPieces);
            if(number1 != number2) {
                done = true;
            }
        }

        listMutations->addData(number1);

        int position1 = matrix->getNodeData(matrix, number1)->getData();
        int position2 = matrix->getNodeData(matrix, number2)->getData();

        matrix->getNodeData(matrix, number1)->setData(position2);
        matrix->getNodeData(matrix, number2)->setData(position1);
    }
}

/// Function that loads the image puzzle map
/// \param matrix
void loadPuzzle(Matrix<int>* matrix)
{
    //Clear the previous tempMap and map
    tempMap.clear();
    puzzleMap.clear();

    //Travel the matrix
    for(int i = 0; i < matrix->getRows(); i++)
    {
        for(int j = 0; j < matrix->getCols(); j++)
        {
            MatrixNode<int>* node = matrix->getNodePos(i,j);
            tempMap.push_back(node->getData());
        }
        puzzleMap.push_back(tempMap);
        tempMap.clear();
    }
}

/// Function that loads the interface of the genetic puzzle
/// \param matrix
/// \param numPieces
/// \param primo
void windowGeneticPuzzle(Matrix<int>* matrix, int numPieces, bool primo)
{
    //Create the window
    RenderWindow window(sf::VideoMode(dimensionX*3,dimensionY+100,32), "Genetic Puzzle");
    window.setVerticalSyncEnabled(true);
    Font font;
    font.loadFromFile("Ubuntu-M.ttf");

    //Adds the matrix generation to the list of generation
    listGenerations->addData(matrix);

    int limitGenerations = numPieces * 75;
    int same = 0;

    //Calculates the function fitness of the actual generation
    int generation = 0;

    loadFitness(listGenerations->getDataPos(generation));

    sf::Vector2f posMapSel1;
    sf::Vector2f posMapSel2;
    sf::Vector2f posMapSel3;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    if(event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if(event.key.code == sf::Keyboard::Right)
                    {
                        //Crossover
                        matrix = crossover(matrix,listFitness);
                        //Mutation
                        if(listMutations->getSize() != 0) {
                            listMutations->delAll();
                            listMutations = new List<int>();
                        }
                        mutation(numPieces,matrix);

                        //Adds new generation
                        listGenerations->addData(matrix);
                        generation++;

                        //Calculates the function fitness of the new generation
                        listFitness->delAll();
                        listFitness = new List<MatrixNode<int>*>();
                        loadFitness(listGenerations->getDataPos(generation));
                    }
                    break;
            }

            //Load the Map
            loadPuzzle(listGenerations->getDataPos(generation));

            //Draw the Puzzle Map
            window.clear(sf::Color::Black);

            float row = dimensionX / matrix->getCols();
            float col = dimensionY / matrix->getRows();

            for (int i = 0; i < puzzleMap.size(); i++) {
                for (int j = 0; j < puzzleMap[i].size(); j++) {
                    sf::Vector2f positionMap = sf::Vector2f(j * row, i * col);
                    sf::Vector2f rect = sf::Vector2f(row, col);
                    sf::Vector2f positionRect = listPosImages->getDataPos(puzzleMap[i][j]);
                    Piece *p = new Piece(positionMap, puzzleTexture, rect, positionRect);
                    window.draw(p->piece);
                }
            }

            //Draw the generation text
            sf::Text textGeneration;
            textGeneration.setFont(font);
            std::string textG = std::to_string(generation);
            textGeneration.setString("Generacion: " + textG);
            textGeneration.setCharacterSize(40);
            textGeneration.setPosition(dimensionX/4, dimensionY+30);
            window.draw(textGeneration);

            //Draw the selection text
            sf::Text textSelection;
            textSelection.setFont(font);
            textSelection.setString("Seleccion:");
            textSelection.setCharacterSize(40);
            textSelection.setPosition(dimensionX + dimensionX/2, 30);
            window.draw(textSelection);

            //Draw the selected individuals
            if(primo)
            {
                posMapSel1 = sf::Vector2f(dimensionX + dimensionX / 2, 100);
                posMapSel2 = sf::Vector2f(dimensionX + dimensionX / 2, 100 + col + 10);
                posMapSel3 = sf::Vector2f(dimensionX + dimensionX / 2, 100 + 2 * col + 20);
            } else if( numPieces <= 10 || numPieces == 14){
                posMapSel1 = sf::Vector2f(dimensionX + dimensionX / 4, 100);
                posMapSel2 = sf::Vector2f(dimensionX + dimensionX / 4 + row + 10, 100);
                posMapSel3 = sf::Vector2f(dimensionX + dimensionX / 4 + 2 * row + 20, 100);
            } else {
                posMapSel1 = sf::Vector2f(dimensionX + dimensionX / 2, 100);
                posMapSel2 = sf::Vector2f(dimensionX + dimensionX / 2 + row + 10, 100);
                posMapSel3 = sf::Vector2f(dimensionX + dimensionX / 2 + 2 * row + 20, 100);
            }

            sf::Vector2f rectSel = sf::Vector2f(row, col);

            sf::Vector2f posRectSel1 = sf::Vector2f(
                    listPosImages->getDataPos(listFitness->getDataPos(0)->getData()));
            sf::Vector2f posRectSel2 = sf::Vector2f(
                    listPosImages->getDataPos(listFitness->getDataPos(1)->getData()));
            sf::Vector2f posRectSel3 = sf::Vector2f(
                    listPosImages->getDataPos(listFitness->getDataPos(2)->getData()));

            Piece *pSel1 = new Piece(posMapSel1, puzzleTexture, rectSel, posRectSel1);
            Piece *pSel2 = new Piece(posMapSel2, puzzleTexture, rectSel, posRectSel2);
            Piece *pSel3 = new Piece(posMapSel3, puzzleTexture, rectSel, posRectSel3);

            window.draw(pSel1->piece);
            window.draw(pSel2->piece);
            window.draw(pSel3->piece);

            window.display();

            //Close the window if it gets to the solution or the limit of generation is achieved
            same = 0;
            for(int x = 0; x < listFitness->getSize(); x++)
            {
                if(listFitness->getDataPos(x)->getH() == 0)
                    same++;
            }

            if(same == numPieces)
            {
                cout << "La imagen ha sido ordenada exitosamente! En: " << generation << " generaciones" << endl;
                sleep(seconds(3));
                window.close();
            }

            if(listGenerations->getSize() == limitGenerations )
            {
                cout << "El limite de generaciones ha sido alcanzado!" << endl;
                sleep(seconds(3));
                window.close();
            }
        }
    }
}

///Main program
int main(int argc, char const *argv[])
{
    Matrix<int> *matrix;
    int numPieces;
    int option;
    bool primo = false;
    string image;

    cout << "Genetic Puzzle\n" << endl;
    cout << "Please enter the name of the image file: " << endl;
    cin >> image;
    cout << "Enter the amount of pieces for the puzzle:" << endl;
    cin >> numPieces;

    while (!primo) {
        int divider = 1, dividers = 0;
        do {
            if (numPieces % divider == 0)
                dividers++;
            divider++;
        } while (divider <= numPieces);

        if (dividers == 2) {
            primo = true;
        }
        break;
    }

    matrix = utility(numPieces, matrix);
    loadPosFitness(matrix);

    loadImages(image, matrix->getRows(), matrix->getCols());

    windowGeneticPuzzle(matrix, numPieces, primo);

    return 0;
}