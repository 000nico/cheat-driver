typedef struct READ_REQUEST {
    HANDLE ProcessId;
    PVOID  Address;
    PVOID  Buffer;
    SIZE_T Size;
};

typedef struct WRITE_REQUEST {
    HANDLE ProcessId;
    PVOID  Address;
    PVOID  Buffer;
    SIZE_T Size;
};