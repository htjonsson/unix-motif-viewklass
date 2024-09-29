#include "PipeHelper.h"

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <iostream>

bool 
PipeHelper::getOutput(FILE *file, std::vector<string>* collection)
{
    char *line = NULL;
    size_t line_length;
    int n=0;

    // https://en.cppreference.com/w/c/experimental/dynamic/getline
    while (getline(&line, &line_length, file) != -1) 
    {
        // std::cout << n++ << "  " << line;
        collection->push_back(std::string(line));
    }

    // End-of-file (good)
    if (feof(file))
    {
        // std::cout << "EOF indicator set" << std::endl;
        return true;
    }

    // https://en.cppreference.com/w/c/io/ferror    
    // Error with file (bad)
    if (ferror(file))
    {
        std::cout << "Error indicator set" << std::endl;
        return false;
    }

    return true;      
}

bool 
PipeHelper::pipeCommand(const char* commandText, std::vector<string>* collection)
{
    char buffer[256];
    FILE *pipe;

    /* use popen to get the files in the directory */
    sprintf (buffer, commandText);
    if (!(pipe = popen(buffer, "r"))) 
    {
        perror (buffer);
        std::cout << buffer << std::endl;

        return false;
    }

    getOutput(pipe, collection);

    // Clean up code

    pclose(pipe);

    return true;
}