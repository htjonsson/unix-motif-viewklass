#ifndef FILE_INFO_ACCESS
#define FILE_INFO_ACCESS

#include<string>

using namespace std;

class FileInfoAccess 
{
private:
    bool _read;
    bool _write;
    bool _execute;
    std::string _name;

public:
    bool read();
    bool write();
    bool execute();
    std::string name();

public:
    void setRead(bool state);
    void setWrite(bool state);
    void setExecute(bool state);
    void setName(const char* name);

public:
    void printOut();

public:
    std::string toString();
};

#endif // FILE_INFO_ACCESS