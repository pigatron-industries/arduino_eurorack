#include "BufferFileReader.h"
#include <Arduino.h>

BufferFileReader::BufferFileReader() {
    this->memPool = nullptr;
}

BufferFileReader::BufferFileReader(MemPool<>& memPool) {
    this->memPool = &memPool;
    this->size = 0;
}

bool BufferFileReader::read(FsFile& file) {
    size = file.size();
    if(memPool == nullptr) {
        buffer = new char[size];
    } else {
        buffer = memPool->allocate(size);
    }
    file.readBytes(buffer, size);
    return true;
}