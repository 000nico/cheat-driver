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

void move_mouse(HANDLE driver, long x, long y, short flag){
    DWORD bytesReturned = 0;

    MOUSE_MOVE_REQUEST req = {};
    req.x = x;
    req.y = y;
    req.flag = flag;

    DeviceIoControl(driver, IOCTL_MOVEMOUSE, &req, sizeof(MOUSE_MOVE_REQUEST), &req, sizeof(MOUSE_MOVE_REQUEST), &bytesReturned, NULL);
}
