/* File:            3-6.c
   Date:            14th July, 2019
   Author:          Dhruv Mohindru
   Description:     program to test file read-write with append mode 
*/
#include "../include/apue.h"
#include <fcntl.h>
#include <string.h>
/* 
From observing output the this program. It is impossible to replace existing data
using lseek if file is open with O_APPEND mode.
*/

int
main(void)
{
    int fd, n, len;
    char *mess = "This another message\n";


    fd = open("myfile", O_RDWR | O_APPEND  , FILE_MODE);

    if (lseek(fd, 0, SEEK_END) == -1)
        printf("seek end error\n");

    if (lseek(fd, -10, SEEK_CUR) == -1)
        printf("seek current error -10\n");
    
    len = strlen(mess);
    if ((n = write(fd, mess, len)) == -1 || n < len)
        printf("write error");

    exit(0);
}