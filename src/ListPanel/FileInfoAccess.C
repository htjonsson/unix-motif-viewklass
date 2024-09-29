#include "FileInfoAccess.h"

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------------------------------------------

bool 
FileInfoAccess::read()
{
    return this->_read;
}

bool 
FileInfoAccess::write()
{
    return this->_write;
}

bool 
FileInfoAccess::execute()
{
    return this->_execute;
}

std::string 
FileInfoAccess::name()
{
    return this->_name;
}

// ---------------------------------------------------------------------------------------------------------------

void 
FileInfoAccess::setRead(bool state)
{
    this->_read = state;
}

void 
FileInfoAccess::setWrite(bool state)
{
    this->_write = state;
}
    
void 
FileInfoAccess::setExecute(bool state)
{
    this->_execute = state;
}

void 
FileInfoAccess::setName(const char* name)
{
    this->_name = std::string(name);
}

// ---------------------------------------------------------------------------------------------------------------

void
FileInfoAccess::printOut()
{
    std::cout << "Read: " << this->read() << std::endl;
    std::cout << "Write: " << this->write() << std::endl;
    std::cout << "Execute: " << this->execute() << std::endl;
}   

std::string
FileInfoAccess::toString()
{
    std::string read((this->read() == true ? "r" : "-"));
    std::string write((this->write() == true ? "w" : "-"));
    std::string execute((this->execute() == true ? "x" : "-"));

    return  read + write + execute;
}