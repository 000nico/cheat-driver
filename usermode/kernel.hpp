#pragma once
#include <windows.h>
#include "shared.hpp"

#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)

bool open_driver(HANDLE* hDriver);
void move_mouse(HANDLE driver, long x, long y, short flags);

template<typename T> T read_memory(HANDLE driver, DWORD pid, PVOID address) {
    T response = { };
    DWORD bytesReturned = 0;

    READ_REQUEST req = { };
    req.ProcessId = (HANDLE)(ULONG_PTR)pid;
    req.Address = address;
    req.Buffer = &response;
    req.Size = sizeof(T);

    bool status = DeviceIoControl(driver, IOCTL_READ, &req, sizeof(READ_REQUEST), &req, sizeof(READ_REQUEST), &bytesReturned, NULL);

    if (status)
        return response;
    else
        return T{};
}

template<typename T> T write_memory(HANDLE driver, DWORD pid, PVOID address, T newValue) {
    T response = { };
    DWORD bytesReturned = 0;

    WRITE_REQUEST req = { };
    req.ProcessId = (HANDLE)(ULONG_PTR)pid;
    req.Address = address;
    req.Buffer = &newValue;
    req.Size = sizeof(T);
    bool status = DeviceIoControl(driver, IOCTL_WRITE, &req, sizeof(WRITE_REQUEST), &req, sizeof(WRITE_REQUEST), &bytesReturned, NULL);

    if (status)
        return response;
    else
        return T{};
}