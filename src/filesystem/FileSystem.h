#ifndef FileSystem_h
#define FileSystem_h

#include <SdFat.h>
#include "FileInfo.h"
#include "reader/FileReader.h"

class FileSystem {
    public:
        FileSystem(const char* rootDirectory = "/"); // Use SDIO
        FileSystem(uint8_t csPin, const char* rootDirectory = "/"); // Use SPI
        void init();

        bool cd(char* directoryPath);
        FileList& ls() { return fileList; }
        bool read(char* filePath, FileReader* fileReader);

    private:
        static SdFat sd;
        
        uint8_t csPin = -1;
        const char* rootDirectory;
        char* currentDirectory;

        FileList fileList;
};

#endif