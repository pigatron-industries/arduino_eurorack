#ifndef BufferFileReader_h
#define BufferFileReader_h

#include <SdFat.h>
#include "FileReader.h"
#include "util/MemPool.h"

class BufferFileReader : public FileReader {
    public:
        BufferFileReader();
        BufferFileReader(MemPool<>& memPool);
        bool read(FsFile& file);

        char* getBuffer() { return buffer; }
        size_t getSize() { return size; }

    private:
        char* buffer;
        size_t size;

        MemPool<>* memPool;
};

#endif