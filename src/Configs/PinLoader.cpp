#include "pinLoader.h"


PinLoader::PinLoader() 
    filePath("Pins/pinconfig.json")
{}

PinLoader::~PinLoader() {}

Json::Value PinLoader::getPins() {
    std::ifstream pinFile();
    Json::Value pins;
    pinFile >> pins;

    return pins;
}

String PinLoader::getFilePath() {
    return filePath;
}