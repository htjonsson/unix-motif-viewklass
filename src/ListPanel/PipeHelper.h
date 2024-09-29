#ifndef PIPE_HELPER
#define PIPE_HELPER

#include <string>
#include <vector>

using namespace std;

class PipeHelper
{
private:
    static bool getOutput(FILE *file, std::vector<string>* collection);
    
public:    
    static bool pipeCommand(const char* commandText, std::vector<string>* collection);
};

#endif // PIPE_HELPER