#include "core/sdk/sdk.hpp"
#include "core/ioctl/ioctl.hpp"

VOID DriverEvtUnload(WDFDRIVER Driver) {
    UNREFERENCED_PARAMETER(Driver);
}

extern "C"
NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
    WDF_DRIVER_CONFIG config;
    WDF_DRIVER_CONFIG_INIT(&config, WDF_NO_EVENT_CALLBACK);
    config.DriverInitFlags = WdfDriverInitNonPnpDriver;
    config.EvtDriverUnload = DriverEvtUnload;

    NTSTATUS status = WdfDriverCreate(DriverObject, RegistryPath, WDF_NO_OBJECT_ATTRIBUTES, &config, WDF_NO_HANDLE);
    if (!NT_SUCCESS(status)) return status;

    UNICODE_STRING sddl = RTL_CONSTANT_STRING(L"D:P(A;;GA;;;SY)(A;;GA;;;BA)");  
    PWDFDEVICE_INIT deviceInit = WdfControlDeviceInitAllocate(WdfGetDriver(), &sddl);

    if (!deviceInit) return STATUS_INSUFFICIENT_RESOURCES;

    UNICODE_STRING deviceName;
    RtlInitUnicodeString(&deviceName, L"\\Device\\ChDriverDevice");
    status = WdfDeviceInitAssignName(deviceInit, &deviceName);
    if (!NT_SUCCESS(status)) return status;

    WDFDEVICE device;
    status = WdfDeviceCreate(&deviceInit, WDF_NO_OBJECT_ATTRIBUTES, &device);
    if (!NT_SUCCESS(status)) return status;

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

    debug_print("[+] Driver loaded\n");
    return STATUS_SUCCESS;
}