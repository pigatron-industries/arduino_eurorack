#ifndef FileSystem_h
#define FileSystem_h

#include <SdFat.h>
#include "FileInfo.h"
#include "reader/FileReader.h"
#include "util/Array.h"

#define MAX_FILE_COUNT 255


typedef Array<FileInfo, MAX_FILE_COUNT> FileList;


class FileSystem {
    public:
        FileSystem(const char* rootDirectory = "/"); // Use SDIO
        FileSystem(uint8_t csPin, const char* rootDirectory = "/"); // Use SPI
        void init();

        bool cd(const char* directoryPath);
        FileList& ls() { return fileList; }
        FileList& ls(const char* extension);
        bool read(const char* filePath, FileReader* fileReader);

    private:
        static SdFat sd;
        
        bool sdio = false;
        uint8_t csPin;
        const char* rootDirectory;
        const char* currentDirectory;

        FileList fileList;
        FileList filteredFileList;

        bool begin();
};

#endif