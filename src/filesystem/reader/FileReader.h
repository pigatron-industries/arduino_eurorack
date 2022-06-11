#ifndef FileReader_h
#define FileReader_h

#include <FS.h> // teensy only
#include <SdFat.h>

class FileReader {
    public:
        virtual bool read(FsFile& file) = 0;
};

#endif