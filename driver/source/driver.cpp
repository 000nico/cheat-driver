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

    status = CreateControlDevice();
    if (!NT_SUCCESS(status)) return status;

    debug_print("[+] Driver loaded\n");
    return STATUS_SUCCESS;
}