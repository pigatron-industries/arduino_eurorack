#include "FileSystem.h"
#include "util/stringutil.h"

SdFat FileSystem::sd;

FileSystem::FileSystem(const char* rootDirectory) :
    rootDirectory(rootDirectory) {
        sdio = true;
}

FileSystem::FileSystem(uint8_t csPin, const char* rootDirectory) : 
    csPin(csPin), rootDirectory(rootDirectory) {
        sdio = false;
}

void FileSystem::init() {
    begin();

    if(!sd.exists(rootDirectory)) {
        Serial.println("Creating root directory");
        sd.mkdir(rootDirectory, true);
    }

    sd.end();
}

bool FileSystem::begin() {
    if(sdio) {
        if (!sd.begin(SdioConfig(FIFO_SDIO))) {
            Serial.println("SDIO card init failed");
            Serial.print(F("SdError: 0X"));
            Serial.print(sd.sdErrorCode(), HEX);
            Serial.print(F(",0X"));
            Serial.println(sd.sdErrorData(), HEX);
            return false;
        }
    } else {
        if (!sd.begin(csPin)) {
            Serial.println("SPI SD card init failed");
            Serial.print(F("SdError: 0X"));
            Serial.print(sd.sdErrorCode(), HEX);
            Serial.print(F(",0X"));
            Serial.println(sd.sdErrorData(), HEX);
            return false;
        }
    }

    return true;
}

bool FileSystem::cd(char* directoryPath) {
    if(!begin()) {
        return false;
    }

    FsFile dir = sd.open(String(rootDirectory) + directoryPath);
    if(dir.isDirectory()) {
        fileList.clear();
        FsFile entry = dir.openNextFile();
        while(entry) {
            FileInfo file;
            entry.getName(file.filename, MAX_FILENAME_SIZE);
            entry.close();
            if(!beginsWith(file.filename, "._")) {
                String filepath = directoryPath + String(file.filename);
                strcpy(file.filepath, filepath.c_str());
                fileList.addFile(file);
            }
            entry = dir.openNextFile();
        }
        dir.close();
        sd.end();
        currentDirectory = directoryPath;
        return true;
    } else {
        dir.close();
        sd.end();
        return false;
    }
}

bool FileSystem::read(char* filePath, FileReader* fileReader) {
    if(!begin()) {
        return false;
    }

    FsFile file = sd.open(String(rootDirectory) + filePath);
    fileReader->read(file);

    file.close();
    sd.end();
    return true;
}