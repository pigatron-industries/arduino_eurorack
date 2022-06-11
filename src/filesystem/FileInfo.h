#ifndef FileInfo_h
#define FileInfo_h

#define MAX_FILENAME_SIZE 32
#define MAX_FILEPATH_SIZE 64
#define MAX_FILE_COUNT 255

class FileInfo {
    public:
        char filename[MAX_FILENAME_SIZE];
        char filepath[MAX_FILEPATH_SIZE];
};

class FileList {
    public:
        void clear() { size = 0; }
        void addFile(FileInfo& file) { files[size] = file; size++; }
        int getSize() { return size; }
        FileInfo& getFile(int index) { return files[index]; }

    private:
        int size = 0;
        FileInfo files[MAX_FILE_COUNT];
};

#endif