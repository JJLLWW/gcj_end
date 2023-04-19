#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <filesystem>

#ifdef DEBUG_HACK
#include "debug_hack.hpp"
#endif

int main(int argc, char **argv) {
    #ifdef DEBUG_HACK
    dh::debug_hack(argv);
    #endif
    int N;
    std::cin >> N;
    N += 1;
    std::cout << N << std::endl;
    int M = N;
}