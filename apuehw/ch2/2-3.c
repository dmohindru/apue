#include "apue.h"
#include <limits.h>
#include <sys/resource.h>

/* If OPEN_MAX is indeterminate, this might be inadequate. */
#define OPEN_MAX_GUESS 256

long
open_max(void)
{
    long openmax;
    struct rlimit r1;

    if ((openmax = sysconf(_SC_OPEN_MAX)) < 0 ||
        openmax == LONG_MAX) {
            if (getrlimit(RLIMIT_NOFILE, &r1) < 0)
                err_sys("can't get file limit");
            if (r1.rlim_max == RLIM_INFINITY)
                openmax = OPEN_MAX_GUESS;
            else
                openmax = r1.rlim_max;
        }
        return openmax;
}