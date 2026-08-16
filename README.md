\# cheat-driver



A lightweight Windows Kernel Driver wrapper designed for memory manipulation and reverse engineering utility development.



\---



\## getting started



\### Prerequisites

\* \*\*C++17\*\* or higher compiler (MSVC recommended)

\* Windows SDK \& WDK (if building driver binaries from source)



\### Integration

To use the driver utilities in your user-mode C++ application, simply include the `kernel.hpp` header:



\#include "kernel.hpp"



\---



\## API Reference



\### `open\_driver`

Establishes a symbolic link / handle connection to the kernel driver.



bool open\_driver(HANDLE\* hDriver);



\* \*\*Parameters:\*\*

&#x20; \* `hDriver` `\[out]`: Pointer to a `HANDLE` variable that receives the driver handle upon success.

\* \*\*Returns:\*\*

&#x20; \* `true` if the driver was successfully opened.

&#x20; \* `false` if the device connection failed.



\---



\### `read\_memory`

Reads memory of a target process through the kernel driver.



template<typename T>

T read\_memory(HANDLE driver, DWORD pid, PVOID address);



\* \*\*Template Parameters:\*\*

&#x20; \* `T`: The type/data structure to read into (e.g., `int`, `uintptr\_t`, `struct Player`).

\* \*\*Parameters:\*\*

&#x20; \* `driver` `\[in]`: Valid driver handle obtained via `open\_driver`.

&#x20; \* `pid` `\[in]`: Process ID of the target application.

&#x20; \* `address` `\[in]`: Base address in the target memory space to read from.

\* \*\*Returns:\*\*

&#x20; \* Value of type `T` read from the target address.



\---



\### `write\_memory`

Writes data to the memory of a target process through the kernel driver.



template<typename T>

bool write\_memory(HANDLE driver, DWORD pid, PVOID address, T newValue);



\* \*\*Template Parameters:\*\*

&#x20; \* `T`: The type of data to write.

\* \*\*Parameters:\*\*

&#x20; \* `driver` `\[in]`: Valid driver handle obtained via `open\_driver`.

&#x20; \* `pid` `\[in]`: Process ID of the target process.

&#x20; \* `address` `\[in]`: Target memory address to write to.

&#x20; \* `newValue` `\[in]`: The value to write into the process address space.



\---



\## 💡 Usage Example



\#include <iostream>

\#include "kernel.hpp"



int main() {

&#x20;   HANDLE hDriver = INVALID\_HANDLE\_VALUE;



&#x20;   if (!open\_driver(\&hDriver)) {

&#x20;       std::cerr << "\[-] Failed to connect to driver." << std::endl;

&#x20;       return 1;

&#x20;   }



&#x20;   std::cout << "\[+] Connected to kernel driver." << std::endl;



&#x20;   DWORD targetPid = 1234; // Target process ID

&#x20;   PVOID targetAddress = (PVOID)0x7FFF0000; // Target address



&#x20;   // Read an integer value

&#x20;   int currentValue = read\_memory<int>(hDriver, targetPid, targetAddress);

&#x20;   std::cout << "\[+] Current Value: " << currentValue << std::endl;



&#x20;   // Write a new integer value

&#x20;   write\_memory<int>(hDriver, targetPid, targetAddress, 1337);

&#x20;   std::cout << "\[+] Value updated!" << std::endl;



&#x20;   CloseHandle(hDriver);

&#x20;   return 0;

}



\---



\## TODO



\- \[ ] \*\*Manual Mapping\*\* (Inject DLLs directly into target process memory without using `CreateRemoteThread`)

\- \[ ] \*\*Kernel Mouse Movement\*\* (Synthetic mouse input via kernel driver to bypass anti-cheat mouse hooks)

\- \[ ] Base Address / Module Base retrieval helper

\- \[ ] Memory allocation / protection modification routines



\---



\## Disclaimer



This project is created strictly for \*\*educational and research purposes\*\*. It is designed to demonstrate kernel-level memory management and Windows OS internals. Using kernel drivers to gain unfair advantages in online video games may violate Terms of Service (ToS) and result in permanent bans or legal action. Use responsibly.

