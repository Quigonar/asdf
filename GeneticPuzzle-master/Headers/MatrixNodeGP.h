#ifndef GENETICPUZZLE_MATRIXNODEGP_H
#define GENETICPUZZLE_MATRIXNODEGP_H

#include <iostream>

/**
 * @file MatrixNodeGP.h
 * @version 1.0
 * @title MatrixNodeGP
 * @brief Manejo de la logica de los nodos de las matrices
 */
using namespace std;

/**
 * @brief Es la clase de los nodos de la matriz
 * @tparam T
 */
template <class T>
class MatrixNodeGP
{
public:
    MatrixNodeGP();
    MatrixNodeGP(T);
    ~MatrixNodeGP();

    T getData();
    void setData(T);
    int getH();
    void setH(int);
    MatrixNodeGP<T>* getRight();
    void setRight(MatrixNodeGP<T>*);
    MatrixNodeGP<T>* getLeft();
    void setLeft(MatrixNodeGP<T>*);
    MatrixNodeGP<T>* getUp();
    void setUp(MatrixNodeGP<T>*);
    MatrixNodeGP<T>* getDown();
    void setDown(MatrixNodeGP<T>*);

    void print();

private:
    T data;
    int H;
    MatrixNodeGP<T>* right = nullptr;
    MatrixNodeGP<T>* left = nullptr;
    MatrixNodeGP<T>* up = nullptr;
    MatrixNodeGP<T>* down = nullptr;
};

/**
 * @brief Es el constructor default
 * @tparam T
 */
template <typename T>
MatrixNodeGP<T>::MatrixNodeGP() {}

/**
 * @brief Es el constructor por parametro
 * @tparam T
 * @param es la informacion del nodo
 */
template <typename T>
MatrixNodeGP<T>::MatrixNodeGP(T data_)
{
    data = data_;
}

/**
 * @brief Es la funcion encargada de retornar la informacion del nodo
 * @tparam T
 * @return retorna la la informacion del nodo
 */
template <typename T>
T MatrixNodeGP<T>::getData()
{
    return MatrixNodeGP::data;
}

/**
 * @brief Es la funcion encargada de cambiar la informacion del nodo
 * @tparam T
 * @param data_ es la nueva informacion del nodo
 */
template <typename T>
void MatrixNodeGP<T>::setData(T data_)
{
    MatrixNodeGP::data = data_;
}

/**
 * @brief Es la funcion que se encarga de retornar la H de la matriz
 * @tparam T
 * @return retorna la H de la matriz
 */
template <typename T>
int MatrixNodeGP<T>::getH()
{
    return MatrixNodeGP::H;
}

/**
 * @brief Es la funcion que se encarga de cambiar la H de la matriz
 * @tparam T
 * @param h es la nueva H de la matriz
 */
template <typename T>
void MatrixNodeGP<T>::setH(int h)
{
    MatrixNodeGP::H = h;
}

/**
 * @brief Es la funcion encargada de retornar el nodo de la derecha
 * @tparam T
 * @return retorna el nodo de la derecha
 */
template <typename T>
MatrixNodeGP<T>* MatrixNodeGP<T>::getRight()
{
    return MatrixNodeGP::right;
}

/**
 * @brief Es la funcion encargada de cambiar el nodo de la derecha
 * @tparam T
 * @param node nuevo nodo
 */
template <typename T>
void MatrixNodeGP<T>::setRight(MatrixNodeGP<T>* node)
{
    MatrixNodeGP::right = node;
}

/**
 * @brief Es la funcion encargada de retornar el nodo de la izquierda
 * @tparam T
 * @return retorna el nodo de la izquierda
 */
template <typename T>
MatrixNodeGP<T>* MatrixNodeGP<T>::getLeft()
{
    return MatrixNodeGP::left;
}

/**
 * @brief Es la funcion encargada de cambiar el nodo de la izquierda
 * @tparam T
 * @param node nuevo nodo
 */
template <typename T>
void MatrixNodeGP<T>::setLeft(MatrixNodeGP<T>* node)
{
    MatrixNodeGP::left = node;
}

/**
 * @brief Es la funcion encargada de retornar el nodo de arriba
 * @tparam T
 * @return retorna el nodo de arriba
 */
template <typename T>
MatrixNodeGP<T>* MatrixNodeGP<T>::getUp()
{
    return MatrixNodeGP::up;
}

/**
 * @brief Es la funcion encargada de cambiar el nodo de arriba
 * @tparam T
 * @param node nuevo nodo
 */
template <typename T>
void MatrixNodeGP<T>::setUp(MatrixNodeGP<T>* node)
{
    MatrixNodeGP::up = node;
}

/**
 * @brief Es la funcion encargada de retornar el nodo de abajo
 * @tparam T
 * @return retorna el nodo de abajo
 */
template <typename T>
MatrixNodeGP<T>* MatrixNodeGP<T>::getDown()
{
    return MatrixNodeGP::down;
}

/**
 * @brief Es la funcion encargada de cambiar el nodo de abajo
 * @tparam T
 * @param node nuevo nodo
 */
template <typename T>
void MatrixNodeGP<T>::setDown(MatrixNodeGP<T>* node)
{
    MatrixNodeGP::down = node;
}

/**
 * @brief Es la funcion encargada de imprimir la informacion del nodo
 * @tparam T
 */
template <typename T>
void MatrixNodeGP<T>::print()
{
    cout << data << " ";
}

/**
 * @brief Es el deconstructor
 * @tparam T
 */
template <typename T>
MatrixNodeGP<T>::~MatrixNodeGP() = default;

#endif //GENETICPUZZLE_MATRIXNODEGP_H
