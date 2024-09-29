#ifndef FILE_INFO
#define FILE_INFO

#include <string>
#include <vector>

#include "FileInfoAccess.h"

using namespace std;

enum class FileInfoType 
{
    FILE = 1,
    DIRECTORY,
    SOCKET,
    LINK,
    FIFO,
    TERMINAL
};

class FileInfo 
{
private:
    std::string _name;
    std::string _directory;
    FileInfoType _type; 
    FileInfoAccess _owner;
    FileInfoAccess _group;
    FileInfoAccess _other;  
    long _size;
    time_t _accessTime;
    time_t _modificationTime;
    time_t _changeTime;

public:
    FileInfoAccess owner();
    FileInfoAccess group();
    FileInfoAccess other(); 
    std::string fullName();
    std::string name();  
    std::string directory();
    long size();
    time_t accessTime();
    time_t modificationTime();
    time_t changeTime();

private:
    void setDirectory(const char* directoryName);
    void setFileName(const char* fileName);
    void setFullFileName(const char* directoryName, const char* fileName);
    void setType(struct stat* fileStat);
    void setSize(long);
    void setOwner(struct stat* fileStat);
    void setGroup(struct stat* fileStat);
    void setOther(struct stat* fileStat);
    void setTimes(struct stat* fileStat);

public:
    static bool getFilesInDirectory(const char* directoryName, std::vector<FileInfo*>* collection);
    static std::string getCurrentWorkingDirectory();
    static std::string getHomeDirectory();

public:
    void printOut();

public:
    static const char* toString(FileInfoType e);
};

#endif // FILE_INFO