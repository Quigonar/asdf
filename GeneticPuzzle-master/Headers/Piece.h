#ifndef GENETICPUZZLE_PIECE_H
#define GENETICPUZZLE_PIECE_H

#include <SFML/Graphics.hpp>
#include <iostream>

/**
 * @file Piece.h
 * @version 1.0
 * @title Piece
 * @brief Manejo de la logica de las piezas del puzzle
 */

/**
 * @brief es la clase de piezas del puzzle
 */
class Piece
{
public:

    sf::Sprite piece;
    float bottom,left,right,top;

    /**
     * @brief Es el constructor default de las piezas
     * @param position es la posicion en la pantalla
     * @param texture es el pedazo de imagen
     * @param rect es el tamano del rectangulo
     * @param posRect es la posicion del rectangulo
     */
    Piece(sf::Vector2f position, sf::Texture &texture, sf::Vector2f rect, sf::Vector2f posRect)
    {
        piece.setTexture(texture);
        piece.setPosition(position);
        piece.setTextureRect(sf::IntRect(posRect.y,posRect.x,rect.x,rect.y));
    }

    /**
     * @brief Es la funcion encargada de actualizar las piezas
     */
    void Update()
    {
        bottom = piece.getPosition().y + piece.getTextureRect().height;
        left = piece.getPosition().x;
        right = piece.getPosition().x + piece.getTextureRect().width;
        top = piece.getPosition().y;
    }
};

#endif //GENETICPUZZLE_PIECE_H
