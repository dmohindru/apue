#include "apue.h"
#include <fcntl.h>
/* if we run this program after creating files foo, bar. There
permissions are not change but their content are chanced */
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)

int
main(void)
{
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		err_sys("creat error for foo");
	/* umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH); */
	umask(S_IRGRP | S_IWGRP | S_IWUSR | S_IRUSR | S_IROTH);
	if (creat("bar", RWRWRW) < 0)
		err_sys("creat error for bar");
	exit(0);
}
