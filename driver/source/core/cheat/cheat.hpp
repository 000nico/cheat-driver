#pragma once
#include <ntifs.h>

NTSTATUS read(HANDLE ProcessId, PVOID Address, PVOID buffer, SIZE_T BufferSize);
NTSTATUS write(HANDLE ProcessId, PVOID buffer, PVOID TargetAddress, SIZE_T BufferSize);