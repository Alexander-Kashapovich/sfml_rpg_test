#pragma once

#include <windows.h>
#include <psapi.h>

class Memometr
{
private:
    PROCESS_MEMORY_COUNTERS pmc;
    HANDLE process;
    int cur_mem = 0;  //kb

public:
    void update();
    int* get_link_memor(){return &cur_mem;}
};