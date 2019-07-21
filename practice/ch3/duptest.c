/* File:            duptest.c
   Date:            12th July, 2019
   Author:          Dhruv Mohindru
   Description:     Simple program to test functionality of dup system call
*/
#include "../include/apue.h"
#include <fcntl.h>
#include <string.h>

int
main(void)
{
    int fd, fd1, len, len1;
    char *mess = "ABCDEFGH - Written from 1st descriptor\n";
    char *mess1 = "abcdefg - Written from 2nd descriptor\n";


    fd = open("myfile.txt", O_RDWR | O_CREAT, FILE_MODE);
    len = strlen(mess);     /* lenght of 1st sting buffer */
    len1 = strlen(mess1);   /* length of 2nd string buffer */
    if (fd == -1)
        printf("error in opening\n");
    
    /* duplicate fd and print both fds */
    fd1 = dup(fd);
    printf("fd: %d\n", fd);
    printf("fd1: %d\n", fd1);
    
    /* write from first descriptor */
    if (write(fd, mess, len) < len)
        printf("Write error first descriptor\n");
    
    /* write from second descriptor */
    if (write(fd1, mess1, len1) < len1)
        printf("Write error second descriptor\n");
    
    exit(0);
}