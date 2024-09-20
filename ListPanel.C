#include <Xm/List.h>



    Arg     args[4];
    int     n = 0;    
    XtSetArg(args[n], XmNbackground, back.pixel); n++;      
    XtSetArg(args[n], XmNforeground, fore.pixel); n++;      
    XtSetValues(list, args, n);


// https://stackoverflow.com/questions/40754380/c-ls-l-implementation-gives-undefined-behavior
// https://man7.org/linux/man-pages/man2/stat.2.html
// https://stackoverflow.com/questions/4989431/how-to-use-s-isreg-and-s-isdir-posix-macros

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string>

using namespace std:

struct {
    bool read;
    bool write;
    bool execute;
} file_info_access_t;

enum file_info_type_e {
    FILE = 1
    DIRECTORY,
    SOCKET,
    LINK,
    FIFO,
    TERMINAL
};

struct {
    std::string name;
    file_info_type_e type; 
    file_info_access_t owner;
    file_info_access_t group;
    file_info_access_t other;  
} file_info_t;

// -----------------------------------------------------------------------------------
    std::vector<string> collection;
    std::vector<file_info_t*> file_collection;

    if(true == getOutput("/bin/ls .", &collection))
    {
        file_info_t file_info;

        for(int i=0; i < collection.size(); i++)
        {
            const char* file_name = collection.at(i);

            std::cout << file_name << std::endl;

            // file_info_t* file_info = new file_info_t;
            
            getFileStat(file_name, &file_info);

            // file_collection.push_back(file_info);
        }
    }

public bool getOutput(FILE *file, std::vector<string>* collection)
{
    char *line = NULL;
    size_t line_length;

    // https://en.cppreference.com/w/c/experimental/dynamic/getline
    while (getline(&line, &line_length, file) != -1) 
    {
        collection.push_back(line);

        // Clean up memory
        free(line);
    }

    // End-of-file (good)
    if (feof(f))
    {
        std::cout << "EOF indicator set" << std::endl;
        return true;
    }

    // https://en.cppreference.com/w/c/io/ferror    
    // Error with file (bad)
    if (ferror(f))
    {
        std::cout << "Error indicator set" << std::endl;
        return false;
    }

    return true;      
}

public bool getOutput(const char* commandText, std::vector<string>* collection)
{
    char buffer[256];
    FILE *pipe;

    /* use popen to get the files in the directory */
    sprintf (buffer, "/bin/ls .");
    if (!(pipe = popen(buffer, "r"))) 
    {
        // perror (buffer);
        return false;
    }

    getOutput(pipe, collection);

    // Clean up code

    pclose(pipe);
}

public bool getFileStat(const char* file_name, file_info_t* file_info)
{
    struct stat file_stat;

    if (stat(file_name, &file_stat) == -1)
        return false;

    getFileType(&file_stat, file_info);
    getFileAccess(&file_stat, file_info);
}

// https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
public void getFileType(stat file_stat, file_info_t* file_info)
{
    file_info.type = getFileType(stat file_stat);
}

public file_info_type_e getFileType(stat file_stat)
{
    // Directory
    if (S_ISDIR(file_stat.st_mode) != 0)
    {
        return DIRECTORY;
    }
    // Socket
    else if (S_ISSOCK(file_stat.st_mode) != 0)  
    {
        return= SOCKET;
    }
    // FIFO special file, or a pipe 
    else if (S_ISFIFO(file_stat.st_mode) != 0)  
    {
        return FIFO;
    }
    // Symbolic link
    else if (S_ISLNK(file_stat.st_mode) != 0)  
    {
        return FIFO;
    }
    // Character special file (a device like a terminal)
    else if (S_ISCHR(file_stat.st_mode) != 0)  
    {
        return TERMINAL;
    }    
    // Others return as a File
    return FILE;
}

// https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
public void getFileAccess(stat file_stat, file_info_t* file_info)
{
    // Owner read
    file_info.owner.read = (fileStat.st_mode & S_IRUSR) ? true : false;

    // Owner write
    file_info.owner.write = (fileStat.st_mode & S_IWUSR) ? true : false;

    // Owner execute
    file_info.owner.execute = (fileStat.st_mode & S_IXUSR) ? true : false;

    // --------------------------------------------------------------------------

    // Group read
    file_info.group.read = (fileStat.st_mode & S_IRGRP) ? true : false;

    // Group read
    file_info.group.write = (fileStat.st_mode & S_IWGRP) ? true : false;

    // Group write
    file_info.group.execute = (fileStat.st_mode & S_IXGRP) ? true : false;

    // --------------------------------------------------------------------------

    // Other's execute
    file_info.other.read = (fileStat.st_mode & S_IROTH) ? true : false;    

    // Other's write
    file_info.other.write = (fileStat.st_mode & S_IWOTH) ? true : false;

    // Other's execute
    file_info.other.execute = (fileStat.st_mode & S_IXOTH) ? true : false;   
}

class ListPanel 
{
    // ------------------------------------------------------------------------------------------------ 

    Widget list_w = XmCreateScrolledList (toplevel, "months", NULL, 0);
    XtVaSetValues (list_w,
        XmNvisibleItemCount,   n,
        // XmNitemCount,          n,
        // XmNitems,              str_list,
        XmNselectionPolicy,    XmMULTIPLE_SELECT,
        NULL);
    XtManageChild (list_w);

    XtAddCallback (list_w, XmNdefaultActionCallback, sel_callback, NULL);
    XtAddCallback (list_w, XmNmultipleSelectionCallback, sel_callback, NULL);

    // ------------------------------------------------------------------------------------------------

    std::vector<string> months;

    months.push_back("January");
    months.push_back("February");
    months.push_back("March");
    months.push_back("April");
    months.push_back("May");
    months.push_back("June");
    months.push_back("July");
    months.push_back("August");
    months.push_back("September");
    months.push_back("October");
    months.push_back("November");
    months.push_back("December");

    // Helper class
    EZ.setItems(w, &months)
}

static class EZ 
{
public: /* XmList */
    static void setItems(Widget widget, const std::vector<std::string>* items);
    static int getSelectedItem(Widget widget, XmListCallbackStruct *cbs)
    static int getSelectedItems(Widget widget, XmListCallbackStruct *cbs, const std::vector<std::int>* selectedItem);

private:
    static void setValues(Widget widget, XmStringTable listTable, int itemCount);

};

public void 
EZ::setItems(Widget widget /* XmList */, const std::vector<std::string>* items)
{
    int itemCount = items->size();

    XmStringTable listTable = (XmStringTable) XtMalloc(itemCount * sizeof (XmString *));

    for (i = 0; i < itemCount; i++)
        listTable[i] = XmStringCreateLocalized (items->at(i));

    // Update the motif list widget

    Ez::setValues(widget, listTable, itemCount);

    // Clean up
    
    for (i = 0; i < n; i++)
        XmStringFree (listTable[i]);
    
    XtFree (listTable);
}

void 
Ez::setValues(Widget widget, XmStringTable listTable, int itemCount)
{
    Arg     args[4];
    int     n = 0;    

    XtSetArg(args[n], XmNitemCount, itemCount); n++;   
    XtSetArg(args[n], XmNitems, listTable); n++;   

    XtSetValues(widget, args, n);
}

public int 
EZ::getSelectedItem(Widget widget /* XmList */, XmListCallbackStruct *cbs)
{
    if (cbs->reason != XmCR_MULTIPLE_SELECT) 
    {
        return cbs->item_position;
    }

    return -1;
}

public int
EZ::getSelectedItems(Widget widget /* XmList */, XmListCallbackStruct *cbs, const std::vector<std::int>* selectedItem)
{
    if (cbs->reason == XmCR_MULTIPLE_SELECT) 
    {
        // printf ("Multiple selection -- %d items selected:\n", cbs->selected_item_count);
        for (i = 0; i < cbs->selected_item_count; i++) 
        {
            // XmStringGetLtoR (cbs->selected_items[i], XmFONTLIST_DEFAULT_TAG, &choice);
            // printf ("%s (%d)\n", choice, cbs->selected_item_positions[i]);
            // XtFree (choice);
            selectedItem.push_back(cbs->selected_item_positions[i]);
        }
        return cbs->selected_item_count
    } 
    else 
    {
        // XmStringGetLtoR (cbs->item, XmFONTLIST_DEFAULT_TAG, &choice);
        // printf ("Default action -- selected item %s (%d)\n", choice, cbs->item_position);
        // XtFree (choice);
        selectedItem->push_back(cbs->item_position);
        
        return 1;
    }
    return -1;
}