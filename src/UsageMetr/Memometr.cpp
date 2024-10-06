#include "Memometr.h"

void Memometr::update()
{
    process = GetCurrentProcess();
    GetProcessMemoryInfo(process,&pmc,sizeof(pmc));
    cur_mem = pmc.WorkingSetSize/1024;
}