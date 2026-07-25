#include <windows.h>

DWORD open_driver(HANDLE* hDriver){
    *hDriver = CreateFileA("\\\\.\\cheatdriver", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

    if(hDriver == INVALID_HANDLE_VALUE) return GetLastError();

    return 1;
}

template<typename T> T read_memory(HANDLE* driver) {
    NTSTATUS status = DeviceIoControl(driver, 0x800,);

    if(NT_SUCESS(status)) {

    }
    else {

    }
}

template<typename T> T write_memory(HANDLE* driver) {
    NTSTATUS status = DeviceIoControl(driver, 0x801);

    if(NT_SUCESS(status)) {
        
    }
    else {

    }
}