
#include <stdio.h>
#include <dirent.h>
#include <curses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <limits.h>
#include <locale.h>
#include <fcntl.h>
#include <pwd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include "config.h"

int raised_signal=-1;
int len=0;
int len_preview=0;
int len_bookmarks=0;
int len_scripts=0;
int selectedFiles = 0;
int i = 0;
int allocSize;
char selected_file[NAME_MAX];
char* dir = NULL;


void displayStatus()
{
    wmove(status_win,1,0);
    wattron(status_win, COLOR_PAIR(2));
    if( SHOW_SELECTION_COUNT == 1 )
    {
        wprintw(status_win,"[%d] ", selectedFiles);
    }
    wprintw(status_win, "(%d/%d)", selection+1, len);
    wprintw(status_win, " %s", dir);
    wattroff(status_win, COLOR_PAIR(2));
    wattron(status_win, COLOR_PAIR(3));
    if(strcasecmp(dir,"/") == 0)
        wprintw(status_win, "%s", selected_file);
    else
        wprintw(status_win, "/%s", selected_file);
    wattroff(status_win, COLOR_PAIR(3));
    wrefresh(status_win);
}




int main(int argc, char* argv[])
{
   
    init(argc, argv);
    curses_init();


    int ch;


    do
    {
     
        int temp_len;

        len = getNumberofFiles(dir);

        if(len <= 0)
            temp_len = 1;
        else
            temp_len = len;

        char* directories[temp_len];

        int status;
        status = getFiles(dir, directories);

        if( status == -1 )
        {
            endwin();
            printf("Couldn't open \'%s\'", dir);
            exit(1);
        }


        allocSize = snprintf(NULL,0,"%s",dir);
        sort_dir = malloc(allocSize+1);
        if(sort_dir == NULL)
        {
            endwin();
            printf("%s\n", "Couldn't allocate memory!");
            exit(1);
        }
        strncpy(sort_dir,dir,allocSize+1);

        if( len > 0 )
            qsort(directories, len, sizeof (char*), compare);

        if(selection > len-1)
        {
            selection = len-1;
        }

        
  

    return 0;
}
