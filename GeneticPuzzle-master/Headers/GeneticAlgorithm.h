#pragma once
#ifndef GENETICPUZZLE_GENETICALGORITHM_H
#define GENETICPUZZLE_GENETICALGORITHM_H
#include "UtilityProgram.h"
#include "Piece.h"
#include "xmlParser.h"
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

/**
 * @file GeneticAlgorithm.h
 * @version 1.0
 * @title GeneticAlgoritm
 * @brief Manejo de la logica del algoritmo genetico
 */
using namespace std;
using namespace sf;

/**
 * @brief Clase GeneticAlgorithm que se encarga de manejar la logica del algoritmo genetico
 */
class GeneticAlgorithm{
public:
    /**
     * @brief Constructor de la clase GeneticAlgorithm
     * @param image es el nombre de la imagen del puzzle
     * @param numPieces es la cantidad de piezas en el cual se quiere partir la imagen
     * @param primo es un booleano que deja saber si la cantidad de piezas es primo o no
     */
    GeneticAlgorithm(string image, int numPieces, bool primo){
        matrix = utility(numPieces, matrix);
        loadPosFitness(matrix);
        loadImages(image, matrix->getRows(), matrix->getCols());
        windowGeneticPuzzle(matrix, numPieces, primo);
    }

    //Different vectors used for the display of the puzzle
    vector <vector<int>> puzzleMap;
    vector <int> tempMap;
    MatrixGP<int> *matrix;

    //Texture of the puzzle and buttons
    Texture puzzleTexture;
    Texture playTexture, rewindTexture, skipTexture;

    //Boolean to of running or stopping
    bool playing = false;

    //Different rectangles for the buttons
    RectangleShape playButton, rewindButton, skipButton, buttonsBackground;

    //Different lists used for the logic of the algorithm
    ListGP<Vector2f>* listPosImages = new ListGP<sf::Vector2f>();
    ListGP<Vector2f>* listPosFitness = new ListGP<sf::Vector2f>();
    ListGP<MatrixNodeGP<int>*>* listFitness = new ListGP<MatrixNodeGP<int>*>();
    ListGP<int>* listMutations = new ListGP<int>();
    ListGP<MatrixGP<int>*>* listGenerations = new ListGP<MatrixGP<int>*>();

    //xml creator
    XmlParser xmlParser;

    //Dimensions of the picture
    float dimensionX;
    float dimensionY;


    /**
     * @brief es la funcion encargada de cargar las imagenes y mantenerlas en variables
     * @param image es el nombre de la imagen que va a ser el fondo
     * @param rows es la cantidad de filas
     * @param cols es la cantidad de columnas
     */
    void loadImages(const string& image, int rows, int cols)
    {
        //Load the texture of the image
        puzzleTexture.loadFromFile(image);
        cout << "Starting to load new textures" << endl;
        playTexture.loadFromFile("PlayButton.png");
        rewindTexture.loadFromFile("RewindButton.png");
        skipTexture.loadFromFile("SkipButton.png");
        cout << "Loaded all textures succesfully" << endl;

        //Get its dimensions
        dimensionX = puzzleTexture.getSize().x;
        dimensionY = puzzleTexture.getSize().y;

        float col = dimensionX / cols;
        float row = dimensionY / rows;

        //Add picture data to the list
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                listPosImages->addData(sf::Vector2f(i*row,j*col));
            }
        }
    }

    /**
     * @brief Es la funcion encargada de ingresar a la lista de fitness la matriz recibida
     * @param matrix es la matriz de la piezas
     */
    void loadPosFitness(MatrixGP<int>* matrix)
    {
        for(int i = 0; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                listPosFitness->addData(sf::Vector2f(i,j));
            }
        }
    }

    /**
     * @brief Es la funcion encargada de ordenar la lista de fitness
     * @param list es la lista de nodos de una matriz
     */
    void sortFitness(ListGP<MatrixNodeGP<int>*>* list)
    {
        MatrixNodeGP<int> *tempData;
        NodeGP<MatrixNodeGP<int>*> *auxNode = list->getHead();
        NodeGP<MatrixNodeGP<int>*> *temp = auxNode;

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

    /**
     * @brief Es la funcion que calcula el fitness de cada individuo
     * @param matrix es la matriz de las piezas
     */
    void loadFitness(MatrixGP<int>* matrix)
    {
        int position;
        int xEnd;
        int yEnd;

        for(int i = 0 ; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                MatrixNodeGP<int>* node = matrix->getNodePos(i, j);
                position = node->getData();
                xEnd = listPosFitness->getDataPos(position).x;
                yEnd = listPosFitness->getDataPos(position).y;
                node->setH(abs(xEnd - i) + abs(yEnd - j));
                listFitness->addData(node);
            }
        }
        sortFitness(listFitness);
    }

    /**
     * @brief Es la funcion encargada de hacer un crossover de individuos
     * @param matrix es la matriz de las piezas
     * @param list es la lista de nodos de una matriz
     * @return retorna la matriz con el nuevo orden
     */
    MatrixGP<int>* crossover(MatrixGP<int>* matrix, ListGP<MatrixNodeGP<int>*>* list)
    {
        int position1 = matrix->getNodeData(matrix,list->getDataPos(0)->getData())->getData();
        int position2 = matrix->getNodeData(matrix,list->getDataPos(1)->getData())->getData();
        int position3 = matrix->getNodeData(matrix,list->getDataPos(2)->getData())->getData();

        matrix->getNodeData(matrix,list->getDataPos(0)->getData())->setData(position3);
        matrix->getNodeData(matrix,list->getDataPos(1)->getData())->setData(position1);
        matrix->getNodeData(matrix,list->getDataPos(2)->getData())->setData(position2);

        return matrix;
    }

    /**
     * @brief Es la funcion encargada de mutar a los individuos
     * @param numPieces es la cantidad de piezas que presenta el puzzle
     * @param matrix es la matriz de las piezas
     */
    void mutation(int numPieces, MatrixGP<int>* matrix)
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

    /**
     * @brief Es la funcion encargada de cargar las piezas de la imagen
     * @param matrix es la matriz de las piezas
     */
    void loadPuzzle(MatrixGP<int>* matrix)
    {
        //Clear the previous tempMap and map
        tempMap.clear();
        puzzleMap.clear();

        //Travel the matrix
        for(int i = 0; i < matrix->getRows(); i++)
        {
            for(int j = 0; j < matrix->getCols(); j++)
            {
                MatrixNodeGP<int>* node = matrix->getNodePos(i, j);
                tempMap.push_back(node->getData());
            }
            puzzleMap.push_back(tempMap);
            tempMap.clear();
        }
    }

    /**
     * @brief Es la funcion encargada de cargar la interfaz del genetic puzzle
     * @param matrix es la matriz de las piezas
     * @param numPieces es la cantidad de piezas
     * @param primo es el booleano que indica si el numero de piezas es primo o no
     */
    void windowGeneticPuzzle(MatrixGP<int>* matrix, int numPieces, bool primo)
    {
        //Create the window
        RenderWindow window(sf::VideoMode(dimensionX,dimensionY+150,32), "Genetic Puzzle");
        window.setVerticalSyncEnabled(true);
        Clock clock;
        Font font;
        font.loadFromFile("Ubuntu-M.ttf");

        //Adds the matrix generation to the list of generations
        MatrixGP<int>* newMatrix = new MatrixGP<int>(matrix->getRows(), matrix->getCols());
        for (int i = 0; i < newMatrix->getRows(); i++){
            for (int j = 0; j < newMatrix->getCols(); j++) {
                newMatrix->setNode(i, j, matrix->getNodePos(i, j)->getData());
            }
        }
        listGenerations->addGeneration(newMatrix);

        int limitGenerations = numPieces * 75;
        int same;

        //Calculates the function fitness of the actual generation
        int generation = 0;
        int generation_ = 0;
        bool doingGens = false;

        loadFitness(listGenerations->getDataPos(generation));

        //Generates all the generations and adds them to a list that will be later drawn
        while (!doingGens)
        {
            //Crossover
            matrix = crossover(matrix,listFitness);
            MatrixGP<int>* newMatrix2 = new MatrixGP<int>(matrix->getRows(), matrix->getCols());
            for (int i = 0; i < newMatrix2->getRows(); i++){
                for (int j = 0; j < newMatrix2->getCols(); j++) {
                    newMatrix2->setNode(i, j, matrix->getNodePos(i, j)->getData());
                }
            }

            //Mutation
            if(listMutations->getSize() != 0) {
                listMutations->delAll();
                listMutations = new ListGP<int>();
            }
            mutation(numPieces,matrix);

            //Adds new generation
            listGenerations->addGeneration(newMatrix2);
            generation_++;

            //Calculates the function fitness of the new generation
            listFitness->delAll();
            listFitness = new ListGP<MatrixNodeGP<int>*>();
            loadFitness(listGenerations->getDataPos(generation_));

            //Close the window if it gets to the solution or the limit of generation is achieved
            same = 0;
            for(int x = 0; x < listFitness->getSize(); x++)
            {
                if(listFitness->getDataPos(x)->getH() == 0)
                    same++;
            }

            if(same == numPieces)
            {
                doingGens = true;
            }

            if(listGenerations->getSize() == limitGenerations )
            {
                doingGens = true;
            }
        }

        for (int i = 0; i < listGenerations->getSize(); i++)
        {
            int rows = listGenerations->getDataPos(i)->getRows();
            int cols = listGenerations->getDataPos(i)->getCols();
            int piece = 1;
            xmlParser.buildGenerationXml(i, rows, cols);
            for (int j = 0; j < listGenerations->getDataPos(i)->getRows(); j++)
            {
                for (int k = 0; k < listGenerations->getDataPos(i)->getCols(); k++)
                {
                    xmlParser.buildPieceXml(piece, j, k, listGenerations->getDataPos(i)->getNodePos(j, k)->getData());
                    piece++;
                }
            }
            xmlParser.saveXml(i);
        }
        loadPuzzle(listGenerations->getDataPos(generation));


        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::MouseButtonPressed)
                {
                    if (event.mouseButton.button == Mouse::Left)
                    {
                        //Click in the play button to run
                        if (playButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && !playing)
                            playing = true;
                        //Click in the play button to stop
                        else if (playButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && playing)
                            playing = false;
                        //Click in the rewind button to go back
                        else if (rewindButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && generation > 0) {
                            generation--;
                            loadPuzzle(listGenerations->getDataPos(generation));
                            playing = false;
                        }
                        //Click in the skip button to go forward
                        else if (skipButton.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y)) && generation < generation_){
                            generation++;
                            loadPuzzle(listGenerations->getDataPos(generation));
                            playing = false;
                        }
                    }
                }
                switch(event.type) {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape)
                            window.close();
                }
                Time timer = clock.getElapsedTime();

                if (generation != generation_ && playing && timer >= seconds(2))
                {
                    //Advance one generation
                    generation++;
                    //Load the Map
                    loadPuzzle(listGenerations->getDataPos(generation));
                    //Pause the reproduction for 2 seconds
                    clock.restart();
                }

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

                //Draws all the buttons
                buttonsBackground.setFillColor(Color(60,60,60,255));
                buttonsBackground.setSize(Vector2f(dimensionX, 150));
                buttonsBackground.setPosition(0,dimensionY);
                playButton.setTexture(&playTexture);
                playButton.setSize(Vector2f(120,120));
                playButton.setPosition((dimensionX/2)-(playButton.getSize().x/2),dimensionY+25);
                rewindButton.setTexture(&rewindTexture);
                rewindButton.setSize(Vector2f(120,120));
                rewindButton.setPosition((dimensionX/4)-(playButton.getSize().x/2),dimensionY+25);
                skipButton.setTexture(&skipTexture);
                skipButton.setSize(Vector2f(120,120));
                skipButton.setPosition((3*dimensionX/4)-(playButton.getSize().x/2),dimensionY+25);

                window.draw(buttonsBackground);
                window.draw(playButton);
                window.draw(rewindButton);
                window.draw(skipButton);

                //Draw the generation text
                Text textGeneration;
                textGeneration.setFont(font);
                string textG = to_string(generation);
                textGeneration.setString("Generation: " + textG + " of " + to_string(generation_) + " generations.");
                textGeneration.setCharacterSize(20);
                textGeneration.setPosition(5, dimensionY+5);
                window.draw(textGeneration);

                window.display();
            }
        }
    }
};

#endif //GENETICPUZZLE_GENETICALGORITHM_H
