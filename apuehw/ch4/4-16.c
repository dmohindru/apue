/* File:        4-16.c
   Author:      Dhruv Mohindru
   Date:        27th July, 2019
   Description: Test program to test conditions of exercise 4-16
*/

#include "apue.h"
#include <fcntl.h>
#include <string.h>

#define MAX         1000
#define NAME        "LongnameLongnameLongnameLongnameLongname"
#define MAXSZ       (10*8192)

int 
main(void)
{
    int i;
    size_t path_size;
    char *path;
    if (chdir("/tmp") < 0)
        err_sys("chdir error");
    for (i = 0; i < MAX; i++) {
        if (mkdir(NAME, DIR_MODE) < 0)
            err_sys("mkdir error");
        if (chdir(NAME) < 0)
            err_sys("chdir error");
    }
    path = path_alloc(&path_size);
    printf("Allocated path size: %ld\n", path_size);

    if (creat("afile", FILE_MODE) < 0)
        err_sys("creat error");
    
    if (getcwd(path, path_size) != NULL) {
        printf("Path Len: %ld\n", strlen(path));
        printf("CWD: %s\n", path);
    }
    
    exit(0);

}