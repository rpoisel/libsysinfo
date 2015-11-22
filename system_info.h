#ifndef SYSTEM_INFO_H
#define SYSTEM_INFO_H

#define MAX_VALUE_LEN 32
#define MAX_FLAGS_LEN 1024

struct cpuinfo
{
    char serial[MAX_VALUE_LEN];
    char bogomips[MAX_VALUE_LEN];
    char flags[MAX_FLAGS_LEN];
};

void parse_cpu_info(struct cpuinfo* info);

#endif /* SYSTEM_INFO_H */
