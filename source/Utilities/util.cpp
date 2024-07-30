#include <time.h>
#include <stdio.h>

int clock_gettime( struct timespec* tv)
{
#ifdef __APPLE__
    clock_gettime(CLOCK_REALTIME, tv);
#else
    timespec_get(tv, TIME_UTC);
#endif
    return (0);
}
