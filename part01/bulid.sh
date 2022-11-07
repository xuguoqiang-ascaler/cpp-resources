#!/bin/bash
g++ -o part01 part01.cpp -O0 -std=c++11 -fno-elide-constructors
# g++ -o part01 part01.cpp -O0 -std=c++17 -fno-elide-constructors
# g++ -o -O0 -std=c++17 -fno-elide-constructors -S part01.cpp 
