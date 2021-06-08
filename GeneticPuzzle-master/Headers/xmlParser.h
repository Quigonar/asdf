#ifndef GENETICPUZZLE_XMLPARSER_H
#define GENETICPUZZLE_XMLPARSER_H
#include "tinyxml.h"
#include <SFML/Graphics.hpp>

/**
 * @file xmlParser.h
 * @version 1.0
 * @title xmlParser
 * @brief Manejo de la logica de la generacion de los archivos XML
 */

/**
 * @brief Es la clase del generador de archivos XML
 */
class XmlParser{
public:
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "UTF-8", "");
    /**
     * @brief Es la funcion encargada de anadir al archivo XML la informacion de la generacion
     * @param generation_ numero de generacion
     * @param generationRows cantidad de filas
     * @param generationCols cantidad de columnas
     */
    void buildGenerationXml (int generation_, int generationRows, int generationCols)
    {
        TiXmlElement* generation = new TiXmlElement("Generation");

        generation->SetAttribute("generationNumber", to_string(generation_));
        generation->SetAttribute("generationRows", to_string(generationRows));
        generation->SetAttribute("generationCols", to_string(generationCols));

        doc.LinkEndChild(decl);
        doc.LinkEndChild(generation);
    }
    /**
     * @brief Es la funcion encargada de anadir al archivo XML la informacion de cada pieza
     * @param piece_ es el numero de pieza
     * @param positionX es la posicion X en la matriz
     * @param positionY es la posicion Y en la matriz
     * @param puzzlePiece es el numero de pieza en la matriz original
     */
    void buildPieceXml(int piece_, int positionX, int positionY, int puzzlePiece)
    {
        TiXmlElement* piece = new TiXmlElement("Piece" + to_string(piece_));

        piece->SetAttribute("positionInMatrix", "(" + to_string(positionX) + "," + to_string(positionY) + ")");
        piece->SetAttribute("solvedPuzzlePieceNumber", puzzlePiece);

        doc.LastChild()->LinkEndChild(piece);
    }
    /**
     * @brief Es la funcion que se encarga de guardar el archivo XML con la informacion anterior
     * @param generation_ es el numero de generacion
     */
    void saveXml(int generation_)
    {
        doc.SaveFile("Generation" + to_string(generation_) + ".xml");
    }
};

#endif //GENETICPUZZLE_XMLPARSER_H
