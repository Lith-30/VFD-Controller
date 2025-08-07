#ifndef PINLOADER_H
#define PINLOADER_H
// #include <string>
#include <fstream>

#include <ArduinoJson.h>

class PinLoader {
    private:
        std::string filePath;

    public:
        PinLoader();
        ~PinLoader();
        Json::Value getPins();
        JsonDocument getFilePath();
};


#endif // PINLOADER_H