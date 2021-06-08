#ifndef GENETICPUZZLE_MATRIX_H_H
#define GENETICPUZZLE_MATRIX_H_H

#include <iostream>

#include "MatrixNodeGP.h"

/**
 * @file MatrixGP.h
 * @version 1.0
 * @title MatrixGP
 * @brief Manejo de la logica de las matrices del genetic puzzle
 */
using namespace std;

/**
 * @brief Es la clase de la matriz del genetic puzzle
 * @tparam T
 */
template <class T>
class MatrixGP
{
public:
    MatrixGP(int, int);
    ~MatrixGP();

    MatrixNodeGP<T>* getFirst();
    int getRows();
    int getCols();

    void setRows(int);
    void setCols(int);

    MatrixNodeGP<T>* getNodePos(int, int);
    MatrixNodeGP<T>* getNodeData(MatrixGP<T>*, T);

    void setNode(int, int, T);

    void printMatrix();

private:
    MatrixNodeGP<T> *first;

    int cols;
    int rows;
};

/**
 * @brief es el constructor por parametros
 * @param rows_ es la cantidad de filas
 * @param cols_ es la cantidad de columnas
 */
template <typename T>
MatrixGP<T>::MatrixGP(int rows_, int cols_)
{
    MatrixGP::rows = rows_;
    MatrixGP::cols = cols_;

    MatrixNodeGP<T> *previousRow = nullptr;

    for(int i = 0; i < rows; ++i)
    {
        MatrixNodeGP<T>* columnNode = new MatrixNodeGP<T>();
        MatrixNodeGP<T>* current = columnNode;

        if(previousRow != nullptr)
        {
            columnNode->setUp(previousRow);
            previousRow->setDown(columnNode);
            previousRow = previousRow->getRight();
        }

        if(i == 0)
            MatrixGP::first = columnNode;

        for(int j = 1; j < cols_; ++j)
        {
            MatrixNodeGP<T> * rowNode = new MatrixNodeGP<T>();
            rowNode->setLeft(current);
            current->setRight(rowNode);

            if(previousRow != nullptr){
                rowNode->setUp(previousRow);
                previousRow->setDown(rowNode);
                previousRow = previousRow->getRight();
            }
            current = rowNode;
        }
        previousRow = columnNode;
    }
}

/**
 * @brief Es la funcion encargada de retornar el primer elemento de la matriz
 * @tparam T
 * @return retorna el primer elemento de la matriz
 */
template <typename T>
MatrixNodeGP<T>* MatrixGP<T>::getFirst()
{
    return MatrixGP::first;
}

/**
 * @brief Es la funcion encargada de retornar la cantidad de filas que tiene la matriz
 * @tparam T
 * @return retorna la cantidad de filas de la matriz
 */
template <typename T>
int MatrixGP<T>::getRows()
{
    return MatrixGP::rows;
}

/**
 * @brief Es la funcion encargada de retornar la cantidad de columnas que tiene la matriz
 * @tparam T
 * @return retorna la cantidad de columnas de la matriz
 */
template <typename T>
int MatrixGP<T>::getCols()
{
    return MatrixGP::cols;
}

/**
 * @brief Es la funcion encargada de cambiar la cantidad de filas que tiene la matriz
 * @tparam T
 */
template <typename T>
void MatrixGP<T>::setRows(int rows_)
{
    MatrixGP::rows = rows_;
}

/**
 * @brief Es la funcion encargada de cambiar la cantidad de columnas que tiene la matriz
 * @tparam T
 */
template <typename T>
void MatrixGP<T>::setCols(int cols_)
{
    MatrixGP::cols = cols_;
}

/**
 * @brief Es la funcion encargada de retornar el nodo por la posicion en la matriz
 * @tparam T
 * @param row es la posicion en fila
 * @param column es la posicion en columna
 * @return retorna el nodo de la matriz
 */
template <typename T>
MatrixNodeGP<T>* MatrixGP<T>::getNodePos(int row, int column)
{
    if(row < rows && column < cols){
        MatrixNodeGP<T>* node = first;

        for (int i = 0; i < row; ++i) {
            node = node->getDown();
        }
        for (int j = 0; j < column; ++j) {
            node = node->getRight();
        }

        return node;
    } else {
        return nullptr;
    }
}

/**
 * @brief Es la funcion encargada de retornar el nodo por la informacion del nodo en la matriz
 * @tparam T
 * @param matrix es la matriz en la cual se busca
 * @param data_ es la informacion del nodo que se busca
 * @return retorna el nodo de la matriz
 */
template <typename T>
MatrixNodeGP<T>* MatrixGP<T>::getNodeData(MatrixGP<T>* matrix, T data_)
{
    for(int i = 0; i < matrix->getRows(); i++)
    {
        for(int j = 0; j < matrix->getCols(); j++)
        {
            MatrixNodeGP<int>* node = matrix->getNodePos(i, j);
            if(node->getData() == data_)
                return node;
        }
    }
}

/**
 * @brief Es la funcion encargada de cambiar la informacion del nood
 * @tparam T
 * @param row es la fila de la matriz
 * @param column es la columna de la matriz
 * @param data_ es la nueva informacion del nodo
 */
template <typename T>
void MatrixGP<T>::setNode(int row, int column, T data_)
{
    if(column < cols && row < rows){
        MatrixNodeGP<T> *node = first;

        for (int i = 0; i < row; ++i) {
            node = node->getDown();
        }

        for (int j = 0; j < column; ++j) {
            node = node->getRight();
        }

        node->setData(data_);
    }
}

/**
 * @brief Es la funcion encargada de imprimir la matriz en consola
 * @tparam T
 */
template <typename T>
void MatrixGP<T>::printMatrix()
{
    MatrixNodeGP<T>* currentColumn = first;

    for(int i = 0; i < rows; i++) {
        currentColumn->print();
        MatrixNodeGP<T>* currentRow = currentColumn->getRight();

        for(int j = 0; j < cols - 1; ++j) {
            currentRow->print();
            currentRow = currentRow->getRight();
        }
        cout << endl;
        currentColumn = currentColumn->getDown();
    }
}

/**
 * @brief Es el deconstructor
 * @tparam T
 */
template<typename T>
MatrixGP<T>::~MatrixGP() = default;

#endif //GENETICPUZZLE_MATRIX_H_H
