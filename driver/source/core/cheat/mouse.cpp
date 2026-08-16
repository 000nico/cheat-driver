#include "cheat.hpp"
#include <ntddk.h>
#include <ntddmou.h>

typedef VOID(*PMOUCLASS_SERVICE_CALLBACKRoutine)(
    PDEVICE_OBJECT DeviceObject,
    PMOUSE_INPUT_DATA InputDataStart,
    PMOUSE_INPUT_DATA InputDataEnd,
    PULONG InputDataConsumed
);

PDEVICE_OBJECT g_ClassDeviceObject = NULL;
PVOID g_ClassService = NULL;

VOID mouse_move(LONG x, LONG y, USHORT flag) {
    if (!g_ClassService || !g_ClassDeviceObject) return;

    MOUSE_INPUT_DATA mouseData = { 0 };
    mouseData.LastX = x;
    mouseData.LastY = y;
    mouseData.Flags = flag;

    ULONG inputConsumed = 0;

    ((PMOUCLASS_SERVICE_CALLBACKRoutine)g_ClassService)(
        g_ClassDeviceObject,
        &mouseData,
        &mouseData + 1,
        &inputConsumed
    );
}