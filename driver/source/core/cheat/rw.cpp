#include "cheat.hpp"
#include "../api/structs.hpp"
#include "../ioctl/shared.h"

NTSTATUS read(READ_REQUEST* request) {
	PEPROCESS source = 0;
	SIZE_T ReturnSize;
	NTSTATUS status = PsLookupProcessByProcessId(request->ProcessId, &source);
	if (!NT_SUCCESS(status)) return status;

	status = MmCopyVirtualMemory(source, request->Address, PsGetCurrentProcess(), request->Buffer, request->Size, UserMode, &ReturnSize);
	
	ObDereferenceObject(source);

	return status;
}

NTSTATUS write(WRITE_REQUEST* request) {
	PEPROCESS source = 0;
	SIZE_T ReturnSize;

	NTSTATUS status = PsLookupProcessByProcessId(request->ProcessId, &source);
	if (!NT_SUCCESS(status)) return status;

	status = MmCopyVirtualMemory(PsGetCurrentProcess(), request->Buffer, source, request->Address, request->Size, UserMode, &ReturnSize);

	ObDereferenceObject(source);

	return status;
}