#pragma once
#include <ntifs.h>
#include <wdf.h>

EVT_WDF_DRIVER_DEVICE_ADD DriverEvtDeviceAdd;
NTSTATUS DriverEvtDeviceAdd(WDFDRIVER Driver, PWDFDEVICE_INIT DeviceInit);
VOID DriverEvtIoDeviceControl(_In_ WDFQUEUE Queue, _In_ WDFREQUEST Request, _In_ size_t OutputBufferLength, size_t InputBufferLength, _In_ ULONG IoControlCode);