#include "kernel.hpp"
#include <iostream>

bool open_driver(HANDLE* hDriver){
    *hDriver = CreateFileA("\\\\.\\ChDriverDevice", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(*hDriver == INVALID_HANDLE_VALUE) {
        std::cout << "error: " << GetLastError() << std::endl;
        return false;
    }

    return true;
}