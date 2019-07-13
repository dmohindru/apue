/* File:            3-2.c
   Date:            11th July, 2019
   Author:          Dhruv Mohindru
   Description:     own implementation of dup2 function without using fcntl function 
*/

#include "../include/apue.h"
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)


int mydup2(int fd, int fd2);  /* our own implementation of dup2 function */

int
main(void)
{
    int fd, fd1;

    fd = open("mytest.file", O_RDWR| O_CREAT, FILE_MODE);

    fd1 = mydup2(fd, 6);

    printf("Descriptor using dup2 function\n");
    printf("fd: %d\n", fd);
    printf("fd1: %d\n", fd1);
    
    /* Using dup function */
    /*  fd1 = dup(fd);

    printf("Descriptor using dup function\n");
    printf("fd: %d\n", fd);
    printf("fd1: %d\n", fd1);

    fd1 = dup(fd);

    printf("Descriptor using dup function\n");
    printf("fd: %d\n", fd);
    printf("fd1: %d\n", fd1);
    */
    exit(0);
}

/*mydup2: own implemenation of dup2 function */
int mydup2(int oldfd, int newfd) 
{
    int max_fd, open_fd[newfd];
    int num_of_fd = 0;
    
    struct stat s;

    /* Check if oldfd is a valid file descriptor */
    if (fstat(oldfd, &s) < 0) {
        errno = EBADF;
        return -1;
    }

    /*Check newfd is in valid range*/
    max_fd = sysconf(_SC_OPEN_MAX);
    //printf("max_fd: %d\n", max_fd);
    if (newfd < 0 || newfd > max_fd)
    {
        errno = EBADF;
        return -1;
    }

    /*If oldfd is equal newfd, return oldfd */
    if (newfd == oldfd)
        return newfd;

    /* new newfd is open close it */
    if(fstat(newfd, &s) == 0)
        close(newfd);


    /* In loop duplicate file descriptors using dup till we get to newfd.
       Then close all opened fds and return newfd  */
    while (1)
    {
        if ((max_fd = dup(oldfd)) == -1) {
            errno = EBADF;
            return -1;
        }
        if (max_fd == newfd) {
            /* close all previously opened fds */
            while (--num_of_fd >= 0)
                close(open_fd[num_of_fd]);
            return max_fd;
        }
        else /* store opened fd */ 
            open_fd[num_of_fd++] = max_fd;
        
    }
}
