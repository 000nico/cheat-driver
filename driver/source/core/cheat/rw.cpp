#include "cheat.hpp"
#include "../api/structs.hpp"

NTSTATUS read(HANDLE ProcessId, PVOID Address, PVOID buffer, SIZE_T BufferSize) {
	PEPROCESS source = 0;
	SIZE_T ReturnSize;
	NTSTATUS status = PsLookupProcessByProcessId(ProcessId, &source);
	if (!NT_SUCCESS(status)) return status;

	status = MmCopyVirtualMemory(source, Address, PsGetCurrentProcess(), buffer, BufferSize, UserMode, &ReturnSize);
	
	ObDereferenceObject(source);

	return status;
}

NTSTATUS write(HANDLE ProcessId, PVOID buffer, PVOID TargetAddress, SIZE_T BufferSize) {
	PEPROCESS source = 0;
	SIZE_T ReturnSize;

	NTSTATUS status = PsLookupProcessByProcessId(ProcessId, &source);
	if (!NT_SUCCESS(status)) return status;

	status = MmCopyVirtualMemory(PsGetCurrentProcess(), buffer, source, TargetAddress, BufferSize, UserMode, &ReturnSize);

	ObDereferenceObject(source);

	return status;
}