#include "core/sdk/sdk.hpp"

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath) {
	debug_print("[+] Driver Started");

	return STATUS_SUCCESS;
}