#include "Processmetr.h"


Processmetr::Processmetr() {
    FILETIME ftIdle, ftKernel, ftUser;

    if (GetSystemTimes(&ftIdle, &ftKernel, &ftUser)) {
        lastSystemKernelTime = FileTimeToULarge(ftKernel);
        lastSystemUserTime = FileTimeToULarge(ftUser);
    }

    HANDLE hProcess = GetCurrentProcess();
    FILETIME ftCreation, ftExit, ftProcKernel, ftProcUser;
    if (GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftProcKernel, &ftProcUser)) {
        lastProcessKernelTime = FileTimeToULarge(ftProcKernel);
        lastProcessUserTime = FileTimeToULarge(ftProcUser);
    }
}

void Processmetr::update() {
    FILETIME ftIdle, ftKernel, ftUser;
    FILETIME ftCreation, ftExit, ftProcKernel, ftProcUser;

    if (!GetSystemTimes(&ftIdle, &ftKernel, &ftUser)) {
        usage_percent  = 0;
    }

    HANDLE hProcess = GetCurrentProcess();
    if (!GetProcessTimes(hProcess, &ftCreation, &ftExit, &ftProcKernel, &ftProcUser)) {
        usage_percent = 0;
    }

    ULARGE_INTEGER sysKernelTime = FileTimeToULarge(ftKernel);
    ULARGE_INTEGER sysUserTime = FileTimeToULarge(ftUser);

    ULARGE_INTEGER procKernelTime = FileTimeToULarge(ftProcKernel);
    ULARGE_INTEGER procUserTime = FileTimeToULarge(ftProcUser);

    ULONGLONG sysTimeDiff = (sysKernelTime.QuadPart - lastSystemKernelTime.QuadPart) +
                            (sysUserTime.QuadPart - lastSystemUserTime.QuadPart);
    ULONGLONG procTimeDiff = (procKernelTime.QuadPart - lastProcessKernelTime.QuadPart) +
                                (procUserTime.QuadPart - lastProcessUserTime.QuadPart);

    lastSystemKernelTime = sysKernelTime;
    lastSystemUserTime = sysUserTime;
    lastProcessKernelTime = procKernelTime;
    lastProcessUserTime = procUserTime;

    if (sysTimeDiff == 0) usage_percent = 0;

    usage_percent = static_cast<int>(procTimeDiff * 100.0 / sysTimeDiff);
}

ULARGE_INTEGER Processmetr::FileTimeToULarge(const FILETIME &ft) {
        ULARGE_INTEGER ul;
        ul.LowPart = ft.dwLowDateTime;
        ul.HighPart = ft.dwHighDateTime;
        return ul;
    }