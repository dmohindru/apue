/* File:        4-17.c
   Author:      Dhruv Mohindru
   Date:        27th July, 2019
   Description: Test program to test conditions of exercise 4-17
*/

#include "apue.h"
#include <fcntl.h>
/* Observation you can create a file in /dev directory.
   But cannot remove file from /dev directory */
int 
main(void) 
{
    char *path = "/dev/fd/1";

     if (unlink(path) < 0)
        err_sys("unlink error");
    
    if (creat(path, FILE_MODE) < 0)
        err_sys("creat error");
    else
        printf("Creat succeded\n");
    
    if (unlink(path) < 0)
        err_sys("unlink error");
    
    exit(0);
}