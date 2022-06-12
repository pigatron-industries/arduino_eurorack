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

        char* getBuffer() { return buffer; }
        size_t getSize() { return size; }

    protected:
        char* buffer;
        size_t size;

        MemPool<>* memPool;

        void allocate(size_t size);
};

#endif