#pragma once 
#include <string>

int clock_gettime( struct timespec* tv);
std::string getDataPath();
#include "RGBColor.hpp"

extern RGBColor yellow;
extern RGBColor brown;
extern RGBColor dark_green;
extern RGBColor orange;
extern RGBColor green;
extern RGBColor light_green;
extern RGBColor dark_yellow;
extern RGBColor blue;
extern RGBColor light_purple;
extern RGBColor dark_purple;