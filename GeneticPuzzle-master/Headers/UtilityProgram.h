#ifndef GENETICPUZZLE_UTILITYPROGRAM_H
#define GENETICPUZZLE_UTILITYPROGRAM_H

#include <iostream>
#include <vector>

#include "MatrixGP.h"
#include "ListGP.h"
/**
 * @file UtilityProgram.h
 * @version 1.0
 * @title Utility
 * @brief Manejo de la logica de la particion de la imagen en una matriz y desordenarla en las piezas definidas
 */
using namespace std;

/**
 * @brief Es la funcion encargada de crear la matriz desordenada y con la cantidad de piezas definidas
 * @param num es la cantida de piezas
 * @param matrix es la matriz
 * @return retorna la matriz desordenada
 */
MatrixGP<int>* utility(int num, MatrixGP<int> *matrix)
{
    ListGP<int> *listInOrder = new ListGP<int>();
    ListGP<int> *listNotOrder = new ListGP<int>();
    bool listUsed[num];
    vector <int> listDividers;

    for(int i = 0; i < num; i++)
    {
        listUsed[i] = false;
        //cout << listUsed[i];
    }
    //cout << endl;

    for(int i = 0; i < num; i++)
        listInOrder->addData(i);
    //listInOrder->print();
    //cout << endl;

    int index = 0;
    for(int i = 0; i < num; i++)
    {
        do{
            index = (rand() % num);
        }
        while(listUsed[index]);
        listNotOrder->addData(listInOrder->getDataPos(index));
        listUsed[index] = true;
    }
    //listNotOrder->print();
    //cout << endl;

    for(int x = 1; x <= num; x++)
    {
        if(num % x == 0)
        {
            listDividers.push_back(x);
        }
    }

    for(int i = 0; i < listDividers.size(); i++)
    {
        //cout << listDividers[i] << endl;
    }
    //cout << endl;

    int middle = listDividers[(listDividers.size() - 1) / 2];

    //cout << middle << endl;

    int higher;
    higher = num / middle;

    matrix = new MatrixGP<int>(higher, middle);


    for(int i = 0; i < matrix->getRows(); ++i)
    {
        for(int j = 0; j < matrix->getCols(); ++j)
        {
            MatrixNodeGP<int>* node = matrix->getNodePos(i, j);
            node->setData(0);
        }
    }
    //matrix->printMatrix();
    //cout << endl;

    int x = 0;
    while(x < listNotOrder->getSize())
    {
        for(int i = 0; i < matrix->getRows(); i++){
            for(int j = 0; j < matrix->getCols(); j++){
                MatrixNodeGP<int>* node = matrix->getNodePos(i, j);
                node->setData(listNotOrder->getDataPos(x));
                x++;
            }
        }
    }
    //matrix->printMatrix();
    //cout << endl;

    return matrix;
}

#endif //GENETICPUZZLE_UTILITYPROGRAM_H
