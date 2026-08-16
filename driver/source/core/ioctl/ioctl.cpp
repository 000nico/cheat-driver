#include "ioctl.hpp"
#include "shared.h"
#include "../cheat/cheat.hpp"

NTSTATUS CreateControlDevice()
{
    UNICODE_STRING sddl = RTL_CONSTANT_STRING(L"D:P(A;;GA;;;SY)(A;;GA;;;BA)");
    PWDFDEVICE_INIT deviceInit = WdfControlDeviceInitAllocate(WdfGetDriver(), &sddl);
    if (!deviceInit) return STATUS_INSUFFICIENT_RESOURCES;

    UNICODE_STRING deviceName;
    RtlInitUnicodeString(&deviceName, L"\\Device\\ChDriverDevice");
    NTSTATUS status = WdfDeviceInitAssignName(deviceInit, &deviceName);
    if (!NT_SUCCESS(status)) {
        WdfDeviceInitFree(deviceInit);
        return status;
    }

    WDFDEVICE device;
    status = WdfDeviceCreate(&deviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) {
        return status;
    }

    UNICODE_STRING symLink;
    RtlInitUnicodeString(&symLink, L"\\DosDevices\\ChDriverDevice");
    status = WdfDeviceCreateSymbolicLink(device, &symLink);
    if (!NT_SUCCESS(status)) return status;

    WDF_IO_QUEUE_CONFIG queueConfig;
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&queueConfig, WdfIoQueueDispatchSequential);
    queueConfig.EvtIoDeviceControl = DriverEvtIoDeviceControl;

    WDFQUEUE queue;
    status = WdfIoQueueCreate(device, &queueConfig, WDF_NO_OBJECT_ATTRIBUTES, &queue);
    if (!NT_SUCCESS(status)) return status;

    WdfControlFinishInitializing(device);
    return STATUS_SUCCESS;
}

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

        case IOCTL_MOVEMOUSE:
        {
            MOUSE_MOVE_REQUEST* req = nullptr;
            status = WdfRequestRetrieveInputBuffer(Request, sizeof(MOUSE_MOVE_REQUEST), (PVOID*)&req, nullptr);
            if (NT_SUCCESS(status)) mouse_move(req->x, req->y, req->flags);
            break;
        }

        default:
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    WdfRequestCompleteWithInformation(Request, status, bytesReturned);
}