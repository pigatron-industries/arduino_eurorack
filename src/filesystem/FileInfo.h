#ifndef FileInfo_h
#define FileInfo_h

#define MAX_FILENAME_SIZE 32
#define MAX_FILEPATH_SIZE 64

class FileInfo {
    public:
        char filename[MAX_FILENAME_SIZE];
        char filepath[MAX_FILEPATH_SIZE];
};


#endif