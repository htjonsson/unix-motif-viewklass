#include "FileInfo.h"

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include <iostream>
#include <map>

// ---------------------------------------------------------------------------------------------------------------

FileInfoAccess 
FileInfo::owner()
{
    return this->_owner;
}

FileInfoAccess 
FileInfo::group()
{
    return this->_group;
}

FileInfoAccess 
FileInfo::other()
{
    return this->_other;
}  

std::string
FileInfo::name()
{
    return this->_name;
}

std::string
FileInfo::directory()
{
    return this->_directory;
}

std::string
FileInfo::fullName()
{
    if (this->_directory.length() > 0 && this->_name.length())
    {
        char buffer[2048];
        sprintf(buffer, "%s/%s", this->_directory.c_str(), this->_name.c_str());
        return std::string(buffer);  
    }
    return std::string(this->_name);
}

long
FileInfo::size()
{
    return this->_size;
}

time_t 
FileInfo::accessTime()
{
    return this->_accessTime;
}

time_t 
FileInfo::modificationTime()
{
    return this->_modificationTime;
}

time_t 
FileInfo::changeTime()
{
    return this->_changeTime;
}

// ---------------------------------------------------------------------------------------------------------------

void 
FileInfo::setDirectory(const char* directoryName)
{
    this->_directory = std::string(directoryName);
}

void 
FileInfo::setFileName(const char* fileName)
{
    this->_name = std::string(fileName);
}

void 
FileInfo::setType(struct stat* fileStat)
{
    // Directory
    if (S_ISDIR(fileStat->st_mode) != 0)
    {
        this->_type = FileInfoType::DIRECTORY;
    }
    // Socket
    else if (S_ISSOCK(fileStat->st_mode) != 0)  
    {
        this->_type = FileInfoType::SOCKET;
    }
    // FIFO special file, or a pipe 
    else if (S_ISFIFO(fileStat->st_mode) != 0)  
    {
        this->_type = FileInfoType::FIFO;
    }
    // Symbolic link
    else if (S_ISLNK(fileStat->st_mode) != 0)  
    {
        this->_type = FileInfoType::LINK;
    }
    // Character special file (a device like a terminal)
    else if (S_ISCHR(fileStat->st_mode) != 0)  
    {
        this->_type = FileInfoType::TERMINAL;
    }    
    // Others return as a File
    else
    {
        this->_type = FileInfoType::FILE;
    }
}

void
FileInfo::setSize(long size)
{
    this->_size = size;
}

void 
FileInfo::setOwner(struct stat* fileStat)
{
    struct passwd *pw = getpwuid(fileStat->st_uid);

    if (pw != NULL)
    {
        this->_owner.setName(pw->pw_name);
    }
    else 
    {
        this->_owner.setName("");
    }

    // --------------------------------------------------------------------------

    // Owner read
    this->_owner.setRead((fileStat->st_mode & S_IRUSR) ? true : false);

    // Owner write
    this->_owner.setWrite((fileStat->st_mode & S_IWUSR) ? true : false);

    // Owner execute
    this->_owner.setExecute((fileStat->st_mode & S_IXUSR) ? true : false);
}

void 
FileInfo::setGroup(struct stat* fileStat)
{
    struct group *gr = getgrgid(fileStat->st_gid);

    if (gr != NULL)
    {
        this->_group.setName(gr->gr_name);
    }
    else 
    {
        this->_group.setName("");
    }

    // --------------------------------------------------------------------------

    // Group read
    this->_group.setRead((fileStat->st_mode & S_IRGRP) ? true : false);

    // Group read
    this->_group.setWrite((fileStat->st_mode & S_IWGRP) ? true : false);

    // Group write
    this->_group.setExecute((fileStat->st_mode & S_IXGRP) ? true : false);        
}

void 
FileInfo::setOther(struct stat* fileStat)
{
    this->_other.setName("");

    // --------------------------------------------------------------------------

    // Other's execute
    this->_other.setRead((fileStat->st_mode & S_IROTH) ? true : false);    

    // Other's write
    this->_other.setWrite((fileStat->st_mode & S_IWOTH) ? true : false);

    // Other's execute
    this->_other.setExecute((fileStat->st_mode & S_IXOTH) ? true : false); 
}

void 
FileInfo::setTimes(struct stat* fileStat)
{
    _accessTime = fileStat->st_atime;
    _modificationTime = fileStat->st_mtime;
    _changeTime = fileStat->st_ctime;
}

// ---------------------------------------------------------------------------------------------------------------

void
FileInfo::printOut()
{
    std::cout << "Name: " << this->name() << std::endl;
    std::cout << "Directory: " << this->directory() << std::endl;
    std::cout << "FileName: " << this->fullName() << std::endl;
    std::cout << "Size: " << this->size() << std::endl;

    std::cout << "Type: " << FileInfo::toString(this->_type) << std::endl;

    std::cout << "Access Time: " << ctime(&this->_accessTime);
    std::cout << "Modification Time: " << ctime(&this->_modificationTime);
    std::cout << "Change Time: " << ctime(&this->_changeTime);
    
    std::cout << "Owner: " << owner().name() << " " << owner().toString() << std::endl;
    std::cout << "Group: " << group().name() << " " << group().toString() << std::endl;
    std::cout << "Other: " << other().name() << " " << other().toString() << std::endl;
}   

// ---------------------------------------------------------------------------------------------------------------

bool
FileInfo::getFilesInDirectory(const char* directoryName, std::vector<FileInfo*>* collection)
{
    DIR *dp = opendir(directoryName);

    if (dp == NULL)
    {
        // fprintf(stderr, "failed to open directory %s (%d: %s)\n", directoryName, errno, strerror(errno));
        std::cout << "failed to open directory (" << errno << ": " << strerror(errno) << ")" << std::endl;

        return false;
    }

    int dfd = dirfd(dp);

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL)
    {
        struct stat fileStat;
        if (fstatat(dfd, dirp->d_name, &fileStat, 0) == -1) 
        {
            fprintf(stderr, "fstatat(\"%s/%s\") failed (%d: %s)\n", directoryName, dirp->d_name, errno, strerror(errno));

            return false;
        }
        else
        {
            FileInfo* pfi = new FileInfo();

            pfi->setFileName(dirp->d_name);
            pfi->setDirectory(directoryName);
            pfi->setType(&fileStat);
            pfi->setGroup(&fileStat);
            pfi->setOwner(&fileStat);
            pfi->setOther(&fileStat);
            pfi->setSize(fileStat.st_size);
            pfi->setTimes(&fileStat);

            collection->push_back(pfi);
        }                  
    }

    // Clean up
    closedir(dp);

    return true;    
}

std::string
FileInfo::getCurrentWorkingDirectory()
{
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) 
    {
        return std::string(cwd);
    }
    return std::string();
}

std::string 
FileInfo::getHomeDirectory()
{
    const char *homedir = getenv("HOME");

    if (homedir != NULL)
       return std::string(homedir); 

    struct passwd *pw = getpwuid(getuid());

    return std::string(pw->pw_dir); 
}

// ---------------------------------------------------------------------------------------------------------------

const char* 
FileInfo::toString(FileInfoType e)
{
    const std::map<FileInfoType,const char*> lookup {
        { FileInfoType::FILE, "File" },
        { FileInfoType::DIRECTORY, "Directory" },
        { FileInfoType::SOCKET, "Socket" },
        { FileInfoType::LINK, "Link" },
        { FileInfoType::FIFO, "Fifo" },
        { FileInfoType::TERMINAL, "Terminal" }
    };
    auto   it  = lookup.find(e);
    return it == lookup.end() ? "" : it->second;
}