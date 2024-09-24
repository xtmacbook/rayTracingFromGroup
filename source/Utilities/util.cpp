#include <time.h>
#include <stdio.h>
#include "util.hpp"

extern RGBColor yellow = RGBColor(1, 1, 0);
extern RGBColor brown = RGBColor(0.71, 0.40, 0.16);
extern RGBColor dark_green = RGBColor(0.0, 0.41, 0.41);
extern RGBColor orange = RGBColor(1, 0.75, 0);
extern RGBColor green = RGBColor(0, 0.6, 0.3);
extern RGBColor light_green = RGBColor(0.65, 1, 0.30);
extern RGBColor dark_yellow = RGBColor(0.61, 0.61, 0);
extern RGBColor blue = RGBColor(0, 0, 1);
extern RGBColor light_purple = RGBColor(0.65, 0.3, 1);
extern RGBColor dark_purple = RGBColor(0.5, 0, 1);

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
    return "../../resources/";
#else
    return "../resources/";
#endif
}
