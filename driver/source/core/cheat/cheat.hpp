#pragma once
#include "../ioctl/shared.h"

NTSTATUS read(READ_REQUEST* request);
NTSTATUS write(WRITE_REQUEST* request);