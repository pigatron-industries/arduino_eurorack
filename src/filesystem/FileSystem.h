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

        bool cd(const char* directoryPath);
        FileList& ls() { return fileList; }
        bool read(const char* filePath, FileReader* fileReader);

    private:
        static SdFat sd;
        
        bool sdio = false;
        uint8_t csPin;
        const char* rootDirectory;
        const char* currentDirectory;

        FileList fileList;

        bool begin();
};

#endif