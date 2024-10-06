#pragma once

#include <windows.h>

class Processmetr{
private:
    ULARGE_INTEGER lastSystemKernelTime;
    ULARGE_INTEGER lastSystemUserTime;
    ULARGE_INTEGER lastProcessKernelTime;
    ULARGE_INTEGER lastProcessUserTime;

    ULARGE_INTEGER FileTimeToULarge(const FILETIME &ft);

    int usage_percent = 0;
public:
    Processmetr();

    void update();

    int* get_cpu_link(){return &usage_percent;}
    
};
