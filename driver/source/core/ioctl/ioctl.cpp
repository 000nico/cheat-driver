#include "ioctl.hpp"
#include "../cheat/cheat.hpp"

#define FILE_DEVICE_DRIVER 0x8000

NTSTATUS DriverEvtDeviceAdd(WDFDRIVER Driver, PWDFDEVICE_INIT DeviceInit)
{
    NTSTATUS status;
    WDFDEVICE device;

    status = WdfDeviceCreate(&DeviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) return status;

    WDF_IO_QUEUE_CONFIG config;
    WDF_IO_QUEUE_CONFIG_INIT_DEFAULT_QUEUE(&config, WdfIoQueueDispatchSequential);
    config.EvtIoDeviceControl = DriverEvtIoDeviceControl;

    WDFQUEUE queue;
    status = WdfIoQueueCreate(device, &config, WDF_NO_OBJECT_ATTRIBUTES, &queue);
    if (!NT_SUCCESS(status)) return status;

    return STATUS_SUCCESS;
}

VOID DriverEvtIoDeviceControl(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, size_t InputBufferLength, _In_ ULONG IoControlCode)
{
    UNREFERENCED_PARAMETER(Queue);
    UNREFERENCED_PARAMETER(OutputBufferLength);
    NTSTATUS status = STATUS_UNSUCCESSFUL;
    size_t bytesReturned = 0;


    switch (IoControlCode) {
        case IOCTL_READ:
            status = read();
            break;

        case IOCTL_WRITE:
            status = write();
            break;

        default:
            status = STATUS_INVALID_DEVICE_REQUEST;
            break;
    }

    WdfRequestCompleteWithInformation(Request, status, bytesReturned);
}