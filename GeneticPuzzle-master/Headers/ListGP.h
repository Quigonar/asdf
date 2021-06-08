#ifndef GENETICPUZZLE_LISTGP_H
#define GENETICPUZZLE_LISTGP_H

#include <iostream>
#include "MatrixGP.h"
#include "NodeGP.h"

/**
 * @file ListGP.h
 * @version 1.0
 * @title ListGP
 * @brief Manejo de las listas
 */
using namespace std;

/**
 * @brief Clase ListGP que se encarga de manejar las listas
 */
template <class T>
class ListGP
{
public:
    ListGP();
    ~ListGP();


    void addData(T);
    void addGeneration(T);
    void delAll();
    void delData(T);
    void print();

    int getSize();
    T getDataPos(int);
    NodeGP<T>* getHead();

private:
    int numNodes;
    NodeGP<T>* head = NULL;
};

/**
 * @brief Es el constructor default
 * @tparam T
 */
template <typename T>
ListGP<T>::ListGP()
{
    numNodes = 0;
    head = NULL;
}

/**
 * @brief Es la funcion encargada de anadir un nodo a la lista
 * @tparam T
 * @param data_ es la informacion que quiere ser guardada en un nodo
 */
template <typename T>
void ListGP<T>::addData(T data_)
{
    NodeGP<T> *newNode = new NodeGP<T>;
    newNode->data = data_;
    newNode->next = NULL;
    NodeGP<T>* temp = head;
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
    numNodes++;
}

/**
 * @brief Es la funcion encargada de anadir una generacion nueva a la lista
 * @tparam T
 * @param data_ es la informacion de la generacion por anadir a la lista
 */
template <typename T>
void ListGP<T>::addGeneration(T data_)
{
    NodeGP<T>* newNode = new NodeGP<T>;
    newNode->data = data_;
    //newMatrix->printMatrix();
    newNode->next = NULL;
    NodeGP<T>* temp = head;
    if (head == NULL)
    {
        newNode->prev = NULL;
        head = newNode;
        //cout << "head: " << head << " - temp: " << temp << endl;
    }
    else{
        while (temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
        //cout << "head: " << head << " - temp: " << temp << endl;
    }
    temp = NULL;
    numNodes++;
}

/**
 * @brief Es la funcion encargada de eliminar todos los nodos de la lista
 * @tparam T
 */
template <typename T>
void ListGP<T>::delAll()
{
    head->delAll();
    head = 0;
}

/**
 * @brief Es la funcion encargada de eliminar un nodo sabiendo la informacion contenida
 * @tparam T
 * @param data_ es la informacion del nodo por eliminar
 */
template <typename T>
void ListGP<T>::delData(T data_)
{
    NodeGP<T> *temp = head;
    NodeGP<T> *temp1 = head->next;

    if(head->data == data_)
    {
        head = temp->next;
        head->prev = NULL;
    } else {
        while(temp1)
        {
            if(temp1->data == data_)
            {
                temp->next = temp1->next;
                temp->prev = temp1->prev->prev;
                temp1 = NULL;
            }
            temp = temp->next;
            temp1 = temp1->next;
        }
    }
    numNodes--;
}

/**
 * @brief Es la funcion encargada de retornar el tamano de la lista
 * @tparam T
 * @return retorna el tamano de la lista
 */
template <typename T>
int ListGP<T>::getSize()
{
    return numNodes;
}

/**
 * @brief Es la funcion encargada de retornar la informacion contenida en un nodo sabiendo el indice
 * @tparam T
 * @param index es el indice del nodo
 * @return retorna la informacion que contiene el nodo
 */
template <typename T>
T ListGP<T>::getDataPos(int index)
{
    NodeGP<T> *temp = head;
    int count = 0;

    while(temp != NULL)
    {
        if(count == index)
        {
            return temp->data;
        }
        count++;
        temp = temp->next;
    }
}

/**
 * @brief Es la funcion encargada de retornar la cabeza de la lista
 * @tparam T
 * @return retorna la cabeza de la lista
 */
template <typename T>
NodeGP<T>* ListGP<T>::getHead() {
    return ListGP::head;
}

/**
 * @brief Es la funcion encargada de imprimir la lista completa
 * @tparam T
 */
template <typename T>
void ListGP<T>::print()
{
    NodeGP<T> *temp = head;
    if(!head){
        cout << "La lista esta vacia" << endl;
    } else {
        while(temp != NULL){
            temp->print();
            temp = temp->next;
        }
    }
}

/**
 * @brief Es el deconstructor
 * @tparam T
 */
template <typename T>
ListGP<T>::~ListGP() = default;

#endif //GENETICPUZZLE_LISTGP_H
