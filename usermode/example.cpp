#include "kernel.hpp"
#include <cstring>
#include <handleapi.h>
#include <iostream>
#include <winuser.h>
#include <TlHelp32.h>

DWORD getPid(const char processName[]){
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(snapshot == INVALID_HANDLE_VALUE) return 0;

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    if(!Process32First(snapshot, &entry)) {
        CloseHandle(snapshot);
        return 0;
    }

    do {
        if(!_stricmp(entry.szExeFile, processName)){
            CloseHandle(snapshot);
            return entry.th32ProcessID;
        }
    }while(Process32Next(snapshot, &entry));

    CloseHandle(snapshot);
    return 0;
}

int main() {
    HANDLE driver;
    DWORD pid = getPid("notepad.exe");

    std::cout << "pid is = " << pid << std::endl;
    
    if(open_driver(&driver) == false) std::cout << "error opening driver" << std::endl;
    else std::cout << "opened driver succesfully" << std::endl;
    
    int number = read_memory<int>(driver, pid, (PVOID)0x868B8FF2C0);
    std::cout << "readed value = " << number << std::endl;

    write_memory<int>(driver, pid, (PVOID)0x868B8FF2C0, 69);
}