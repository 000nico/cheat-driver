\# cheat-driver



im new to kernel driver developing, so im currently developing this driver with utilities for game cheats



\## Documentation



Include `kernel.hpp` to your project in order to use these functions



```bool open\_driver(HANDLE\* hDriver);```

Creates a link to the driver, return true if the driver is successfully opened, or false if there was an error. 

Returns by pointer the HANDLE to the driver



```template<typename T> T read\_memory(HANDLE driver, DWORD pid, PVOID address);```

Pretty self-explanatory. 

Give in HANDLE the one you got with `open\_driver`, pid from the process that you are trying to read from, address that you want to read



```template<typename T> T write\_memory(HANDLE driver, DWORD pid, PVOID address, T newValue)```

Give the HANDLE that you got with `open\_driver`, pid fromm the process that you are trying to write in, address that you want to write on, and the new value



\## TO-DO

manual mapping

mouse movement



