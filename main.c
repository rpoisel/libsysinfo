#include "system_info.h"
#include <stdio.h>

int main(void)
{
    struct cpuinfo info;
    parse_cpu_info(&info);

    printf("Serial: %s, Bogomips: %s, Flags: %s\n", 
        info.serial,
        info.bogomips,
        info.flags);
}
