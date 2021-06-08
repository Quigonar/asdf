#pragma once
#ifndef GENETICPUZZLE_NODEGP_H
#define GENETICPUZZLE_NODEGP_H

#include <iostream>

/**
 * @file NodeGP.h
 * @version 1.0
 * @title NodeGP
 * @brief Manejo de la logica de los nodos de las listas
 */
using namespace std;

/**
 * @brief Es la clase de los nodos de la lista
 * @tparam T
 */
template <class T>
class NodeGP
{
public:
    NodeGP *next;
    NodeGP *prev;
    T data;

    void delAll();
    void print();
};

/**
 * @brief Es la funcion encargada de eliminar todos los nodos de una lista
 * @tparam T
 */
template <typename T>
void NodeGP<T>::delAll()
{
    if (next)
        next->delAll();
    delete this;
}

template<typename T>
/**
 * @brief Es la funcion encargada de imprimir la informacion contenida en el nodo
 * @tparam T
 */
void NodeGP<T>:: print()
{
    cout << data << endl;
}

#endif //GENETICPUZZLE_NODEGP_H
