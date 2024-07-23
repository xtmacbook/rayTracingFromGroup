#include <time.h>

int clock_gettime( struct timespec* tv)
{
    timespec_get(tv, TIME_UTC);
    return (0);
}