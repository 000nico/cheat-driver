# cheat-driver

A lightweight Windows Kernel Driver wrapper designed for memory manipulation and reverse engineering utility development.

---

## getting started

### Prerequisites
* **C++17** or higher compiler (MSVC recommended)
* Windows SDK & WDK (if building driver binaries from source)

### Integration
To use the driver utilities in your user-mode C++ application, simply include the `kernel.hpp` header:

#include "kernel.hpp"

---

## API Reference

### `open_driver`
Establishes a symbolic link / handle connection to the kernel driver.

bool open_driver(HANDLE* hDriver);

* **Parameters:**
  * `hDriver` `[out]`: Pointer to a `HANDLE` variable that receives the driver handle upon success.
* **Returns:**
  * `true` if the driver was successfully opened.
  * `false` if the device connection failed.

---

### `read_memory`
Reads memory of a target process through the kernel driver.

template<typename T>
T read_memory(HANDLE driver, DWORD pid, PVOID address);

* **Template Parameters:**
  * `T`: The type/data structure to read into (e.g., `int`, `uintptr_t`, `struct Player`).
* **Parameters:**
  * `driver` `[in]`: Valid driver handle obtained via `open_driver`.
  * `pid` `[in]`: Process ID of the target application.
  * `address` `[in]`: Base address in the target memory space to read from.
* **Returns:**
  * Value of type `T` read from the target address.

---

### `write_memory`
Writes data to the memory of a target process through the kernel driver.

template<typename T>
bool write_memory(HANDLE driver, DWORD pid, PVOID address, T newValue);

* **Template Parameters:**
  * `T`: The type of data to write.
* **Parameters:**
  * `driver` `[in]`: Valid driver handle obtained via `open_driver`.
  * `pid` `[in]`: Process ID of the target process.
  * `address` `[in]`: Target memory address to write to.
  * `newValue` `[in]`: The value to write into the process address space.

---

## Usage Example

#include <iostream>
#include "kernel.hpp"

int main() {
    HANDLE hDriver = INVALID_HANDLE_VALUE;

    if (!open_driver(&hDriver)) {
        std::cerr << "[-] Failed to connect to driver." << std::endl;
        return 1;
    }

    std::cout << "[+] Connected to kernel driver." << std::endl;

    DWORD targetPid = 1234; // Target process ID
    PVOID targetAddress = (PVOID)0x7FFF0000; // Target address

    // Read an integer value
    int currentValue = read_memory<int>(hDriver, targetPid, targetAddress);
    std::cout << "[+] Current Value: " << currentValue << std::endl;

    // Write a new integer value
    write_memory<int>(hDriver, targetPid, targetAddress, 1337);
    std::cout << "[+] Value updated!" << std::endl;

    CloseHandle(hDriver);
    return 0;
}

---

## TODO

- [ ] **Manual Mapping** (Inject DLLs directly into target process memory without using `CreateRemoteThread`)
- [ ] **Kernel Mouse Movement** (Synthetic mouse input via kernel driver to bypass anti-cheat mouse hooks)
- [ ] Base Address / Module Base retrieval helper
- [ ] Memory allocation / protection modification routines

---

## Disclaimer

This project is created strictly for **educational and research purposes**. It is designed to demonstrate kernel-level memory management and Windows OS internals. Using kernel drivers to gain unfair advantages in online video games may violate Terms of Service (ToS) and result in permanent bans or legal action. Use responsibly.