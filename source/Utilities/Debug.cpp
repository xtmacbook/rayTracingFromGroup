#include "Debug.hpp"
#include <string>
#include <iostream>

void debug_print(const char* s)
{
      if(DEBUG){
        std::cout << s;
    }
}