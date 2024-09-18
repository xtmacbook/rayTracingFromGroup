#include <time.h>
#include <stdio.h>
#include "util.hpp"

int clock_gettime( struct timespec* tv)
{
#ifdef __APPLE__
    clock_gettime(CLOCK_REALTIME, tv);
#else
    timespec_get(tv, TIME_UTC);
#endif
    return (0);
}

std::string getDataPath()
{
#ifdef __APPLE__
    return std::string();
#else
    return "../resources/";
#endif
}
