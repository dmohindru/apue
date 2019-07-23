/* File:        4-6.c
   Author:      Dhruv Mohindru
   Date:        23th July, 2019
   Description: cp(1) utility which copies file containing holes without writing the 
                bytes of 0 to output file */
#include "apue.h"
#include <stdio.h>
#include <fcntl.h>

static int all_zeros(char *buf, size_t buf_size);

int
main(int argc, char *argv[])
{
    int fd_src, fd_dest, n;
    size_t buf_size;
    struct stat	buf;
    char *read_buf;

    /* Check for proper command line argument */
    if (argc != 3)
        err_quit("usage: %s <src> <dest>", argv[0]);
    
    /* Open source file for reading */
    if ((fd_src = open(argv[1], O_RDONLY, FILE_MODE)) <  0) {
        err_sys("%s", argv[1]);
        exit(-1);
    }    
    /* Create destination file for writing */
    if ((fd_dest = creat(argv[2], FILE_MODE)) < 0)
        err_sys("%s", argv[2]);
    
    /* Read source file stats structure */
    if (fstat(fd_src, &buf) < 0)
        err_sys("fstat error");
    /* Display best io block size */
    /* printf("Best block io size: %ld\n",buf.st_blksize); */

    /* Read block io size */
    buf_size = buf.st_blksize;

    /* Allocate read buffer of size buf.st_blksize for best results*/
    read_buf = malloc(buf_size);
    if (read_buf == NULL)
        err_quit("Read buffer allocatoin error");

    /* Read contents of source file and write to destination file */
    while ((n = read(fd_src, read_buf, buf_size)) > 0) {
        if (all_zeros(read_buf, buf_size) == 0)
		    if (write(fd_dest, read_buf, n) != n)
			    err_sys("write error");
    }

    /* Close source file */
    if (close(fd_src) < 0)
        err_sys("Close error on source file");
    /* Close destination file */
    if (close(fd_dest) < 0)
        err_sys("Close error on destination file");

    exit(0);

}

/*allzeros: returns true (1) if buf contains all zeros, 0 otherwise*/
static int all_zeros(char *buf, size_t buf_size)
{
    int i;
    for (i = 0; i < buf_size; i++)
        if (buf[i] != 0)
            return 0;
    return 1;
}