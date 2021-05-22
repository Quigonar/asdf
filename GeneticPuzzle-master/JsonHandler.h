#ifndef GENETICPUZZLE_MASTER_JSONHANDLER_H
#define GENETICPUZZLE_MASTER_JSONHANDLER_H
#include <SFML/Network.hpp>
#include "rapidjson/document.h"

using namespace std;
using namespace sf;
using namespace rapidjson;

class JsonHandler {
public:
    string send(string image, int numPieces, bool primo)
    {
        string jsonStr = R"({"image":")" + image + R"(","numPieces":")" + to_string(numPieces) + R"(","variable":")" + to_string(primo) + "\"}";
        return jsonStr;
    }
};

#endif //GENETICPUZZLE_MASTER_JSONHANDLER_H
