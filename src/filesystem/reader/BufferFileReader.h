#ifndef BufferFileReader_h
#define BufferFileReader_h

#include <SdFat.h>
#include "FileReader.h"
#include "memory/MemPool.h"

class BufferFileReader : public FileReader {
    public:
        BufferFileReader();
        BufferFileReader(MemPool<>& memPool);
        bool read(FsFile& file);

        unsigned char* getBuffer() { return buffer; }
        size_t getSize() { return size; }

    protected:
        unsigned char* buffer;
        size_t size;

        MemPool<>* memPool;

        void allocate(size_t size);
};

#endif