#pragma once
#include <ntifs.h>

#ifdef __cplusplus
extern "C" {
#endif

    NTSTATUS NTAPI MmCopyVirtualMemory(
        PEPROCESS SourceProcess,
        PVOID SourceAddress,
        PEPROCESS TargetProcess,
        PVOID TargetAddress,
        SIZE_T BufferSize,
        KPROCESSOR_MODE PreviousMode,
        PSIZE_T ReturnSize
    );

#ifdef __cplusplus
}
#endif