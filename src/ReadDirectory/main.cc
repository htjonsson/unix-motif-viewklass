#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>
#include <iostream>

#include <sqlite3.h>

using namespace std;

extern void sqliteVersion();
extern int directoryRead(); 

// Application-specific setup
int 
main ( int argc, char **argv )
{
    sqliteVersion();

    return directoryRead();
}

/*
    Check if file exists

    if (access(fname, F_OK) == 0) {
    // file exists
    } else {
        // file doesn't exist
    }

*/

// https://zetcode.com/db/sqlitec/

void 
sqliteVersion()
{
    std::cout << "SQLITE VERSION" << endl;

    std::cout << sqlite3_libversion() << endl;

    sqlite3* db;
    sqlite3_stmt* stmt;

    int resultCode = sqlite3_open(":memory:", &db);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    resultCode = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &stmt, 0);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "Failed to fetch data: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;   
    }

    resultCode = sqlite3_step(stmt);

    if (resultCode == SQLITE_ROW) 
    {
        std::cout << sqlite3_column_text(stmt, 0) << endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
}

void
sqliteCreateTable()
{
    sqlite3* db;
    char* errorMessage = 0;

    std::cout << "SQLITE CREATE TABLE" << endl;

    int resultCode = sqlite3_open(":memory:", &db);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }

    const char *sql = "CREATE TABLE Friends(Id INTEGER PRIMARY KEY, Name TEXT);"
        "INSERT INTO Friends(Name) VALUES ('Tom');"
        "INSERT INTO Friends(Name) VALUES ('Rebecca');"
        "INSERT INTO Friends(Name) VALUES ('Jim');"
        "INSERT INTO Friends(Name) VALUES ('Roger');"
        "INSERT INTO Friends(Name) VALUES ('Robert');";

    resultCode = sqlite3_exec(db, sql, 0, 0, &errorMessage);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "Failed to create table" << endl;
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return;       
    }
    else
    {
        std::cout << "Table Friends created successfully" << endl;
    }   

    int lastId = sqlite3_last_insert_rowid(db);

    std::cout << "The last Id of the inserted row is " << lastId << endl;

    sqlite3_close(db);          
}

void
sqliteInsert()
{
    std::cout << "SQLITE INSERT" << endl;

    sqlite3* db;
    char* errorMessage = 0;

    int resultCode = sqlite3_open("test.db", &db);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "Cannot open database: " << sqlite3_errmsg(db) << endl;
        sqlite3_close(db);
        return;
    }   

    const char *sql = "DROP TABLE IF EXISTS Cars;" 
                "CREATE TABLE Cars(Id INT, Name TEXT, Price INT);" 
                "INSERT INTO Cars VALUES(1, 'Audi', 52642);" 
                "INSERT INTO Cars VALUES(2, 'Mercedes', 57127);" 
                "INSERT INTO Cars VALUES(3, 'Skoda', 9000);" 
                "INSERT INTO Cars VALUES(4, 'Volvo', 29000);" 
                "INSERT INTO Cars VALUES(5, 'Bentley', 350000);" 
                "INSERT INTO Cars VALUES(6, 'Citroen', 21000);" 
                "INSERT INTO Cars VALUES(7, 'Hummer', 41400);" 
                "INSERT INTO Cars VALUES(8, 'Volkswagen', 21600);";

    resultCode = sqlite3_exec(db, sql, 0, 0, &errorMessage);

    if (resultCode != SQLITE_OK)
    {
        std::cout << "SQL error: " << errorMessage << endl;
        sqlite3_free(errorMessage);
        sqlite3_close(db);
        return;       
    }   

    sqlite3_close(db);
}

int 
directoryRead()
{
    struct passwd *pw = getpwuid(getuid());

    std::string userDirectory(pw->pw_dir);
    std::string homeDirectory(getenv("HOME"));

    // std::cout << "getcwd " << getcwd() <<  endl;
    std::cout << "pw->pw_dir " << userDirectory << endl;
    std::cout << "getenv(\"HOME\") " << homeDirectory << endl;
    // std::cout << << endl;

    char *cwd = getcwd(NULL,0);
    std::cout << "Working directory " << cwd << endl;

    DIR *dir = opendir(homeDirectory.c_str());
    
    struct dirent   *info;
    struct stat     statBuffer;
    struct passwd   *user;
    struct group    *grp;
    struct tm       *tm;

    while((info = readdir(dir)))
    {
        std::string path(homeDirectory + "/" + info->d_name);

        std::cout << "file with path " << path << endl;

        stat(path.c_str(), &statBuffer);
        std::cout << "file " << info->d_name << endl;

        user = getpwuid(statBuffer.st_uid);
        std::cout << "uid " << statBuffer.st_uid << " " << user->pw_name << endl;

        grp = getgrgid(statBuffer.st_gid);
        std::cout << "gid " << statBuffer.st_gid << " " << grp->gr_name << endl;

        std::cout 
            << ((S_IRUSR & statBuffer.st_mode) ? 'r' : '-')
            << ((S_IWUSR & statBuffer.st_mode) ? 'w' : '-')
            << ((S_IXUSR & statBuffer.st_mode) ? 'x' : '-')
            << ((S_IRGRP & statBuffer.st_mode) ? 'r' : '-')
            << ((S_IWGRP & statBuffer.st_mode) ? 'w' : '-')
            << ((S_IXGRP & statBuffer.st_mode) ? 'x' : '-')
            << ((S_IROTH & statBuffer.st_mode) ? 'r' : '-')
            << ((S_IWOTH & statBuffer.st_mode) ? 'w' : '-')
            << ((S_IXOTH & statBuffer.st_mode) ? "x" : "-")
            << endl;

        std::cout << "size " << statBuffer.st_size << endl;

        std::cout << "dir " << (S_ISDIR(statBuffer.st_mode) ? "Y" : "N" ) << endl;

        tm = localtime(&statBuffer.st_mtime);

        char stringBuffer[80];
        // https://cplusplus.com/reference/ctime/strftime/
        strftime(stringBuffer, sizeof(stringBuffer), "%FT%T", tm);

        std::cout << "date " << stringBuffer << endl;

    }

    return 0;
}