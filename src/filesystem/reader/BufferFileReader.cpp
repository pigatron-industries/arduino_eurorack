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
    allocate(size);
    file.readBytes(buffer, size);
    return true;
}

void BufferFileReader::allocate(size_t size) {
    if(memPool == nullptr) {
        buffer = new unsigned char[size];
    } else {
        buffer = memPool->allocate(size);
    }
}