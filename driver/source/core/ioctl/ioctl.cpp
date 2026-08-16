#include "ioctl.hpp"
#include "shared.h"
#include "../cheat/cheat.hpp"

VOID DriverEvtIoDeviceControl(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    UNREFERENCED_PARAMETER(InputBufferLength);
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    size_t bytesReturned = 0;

    switch (IoControlCode) {
        case IOCTL_READ:
        {
            READ_REQUEST* req = nullptr;
            status = WdfRequestRetrieveInputBuffer(Request, sizeof(READ_REQUEST), (PVOID*)&req, nullptr);
            if (NT_SUCCESS(status)) status = read(req);
            break;
        }

        case IOCTL_WRITE:
        {
            WRITE_REQUEST* req = nullptr;
            status = WdfRequestRetrieveInputBuffer(Request, sizeof(WRITE_REQUEST), (PVOID*)&req, nullptr);
            if (NT_SUCCESS(status)) status = write(req);
            break;
        }

        default:
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    WdfRequestCompleteWithInformation(Request, status, bytesReturned);
}