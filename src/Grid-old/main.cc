#include <Xm/Xm.h>
#include <Xm/Form.h>
#include <Xm/DrawingA.h>
#include <Xm/Label.h>
#include <Vk/VkApp.h>
#include <iostream>
#include "IGrid.h"

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <grp.h>

using namespace std;

// Application-specific setup
int main ( int argc, char **argv )
{
	const char* const defaultResources[] = {
		"+*background : gray80",
        "*renderTable : xft",
        "*xft.fontType : FONT_IS_XFT",
        "*xft.fontName : helvetica",
        "*xft.fontSize : 10",
        "*xft.fontStyle : regular",
		NULL,
	};

    VkApp* app = new VkApp("IGridApp", &argc, argv);

    app->setDefaultResources(app->baseWidget(), defaultResources);

    VkSimpleWindow* win = new VkSimpleWindow("IGrid - App");

    IGrid* view = new IGrid((char*)std::string("grid").c_str(), win->mainWindowWidget());

    XtVaSetValues (view->baseWidget(),
        XmNheight, 800,
        XmNwidth, 600,
        NULL);

    win->addView(view);

    struct passwd *pw = getpwuid(getuid());

    std::string userDirectory(pw->pw_dir);
    std::string homeDirectory(getenv("HOME"));

    // std::cout << "getcwd " << getcwd() <<  endl;
    std::cout << "pw->pw_dir " << userDirectory << endl;
    std::cout << "getenv(\"HOME\") " << homeDirectory << endl;
    // std::cout << << endl;

    char *cwd = getcwd(NULL,0);
    std::cout << "Working directory " << cwd << endl;


    struct dirent *info;
    DIR *dir = opendir(homeDirectory.c_str());
    struct stat sb;
    struct passwd *user;
    struct group *grp;

    while((info = readdir(dir)))
    {
        std::string path(homeDirectory + "/" + info->d_name);

        std::cout << "file with path " << path << endl;

        stat(path.c_str(), &sb);
        std::cout << "file " << info->d_name << endl;

        user = getpwuid(sb.st_uid);
        std::cout << "uid " << sb.st_uid << " " << user->pw_name << endl;

        grp = getgrgid(sb.st_gid);
        std::cout << "gid " << sb.st_gid << " " << grp->gr_name << endl;

        std::cout 
            << ((S_IRUSR & sb.st_mode) ? 'r' : '-')
            << ((S_IWUSR & sb.st_mode) ? 'w' : '-')
            << ((S_IXUSR & sb.st_mode) ? 'x' : '-')
            << ((S_IRGRP & sb.st_mode) ? 'r' : '-')
            << ((S_IWGRP & sb.st_mode) ? 'w' : '-')
            << ((S_IXGRP & sb.st_mode) ? 'x' : '-')
            << ((S_IROTH & sb.st_mode) ? 'r' : '-')
            << ((S_IWOTH & sb.st_mode) ? 'w' : '-')
            << ((S_IXOTH & sb.st_mode) ? "x" : "-")
            << endl;

        std::cout << "size " << sb.st_size << endl;

        std::cout << "dir " << (S_ISDIR(sb.st_mode) ? "Y" : "N" ) << endl;
    }

    win->show();
    app->run();  // Run the application

    return 0;
}