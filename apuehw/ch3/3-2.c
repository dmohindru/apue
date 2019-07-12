/* File:            3-2.c
   Date:            11th July, 2019
   Author:          Dhruv Mohindru
   Description:     own implementation of dup2 function without using fcntl function 
*/

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


int mydup2(int fd, int fd2);  /* our own implementation of dup2 function */

int
main(void)
{
    int fd, fd1;

    fd = open("mytest.file", O_RDWR| O_CREAT);

    fd1 = dup2(fd, 12);

    printf("fd: %d\n", fd);
    printf("fd1: %d\n", fd1);

    exit(0);
}

/*mydup2: own implemenation of dup2 function */
int mydpu2(int fd, int fd2)
{

    /* don't forget to close previous fd2 file descriptor */

}
