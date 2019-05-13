#ifndef MEM_H
#define MEM_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QString>

typedef struct MEM_USE_STATE
{
    unsigned int memtotal;
    unsigned int memfree;
}MEM_USE_STATE;

float get_mem_rate()
{
    FILE *fp;
    MEM_USE_STATE mem_use_state;
    float memused, memtotal, rate;
    char state[256];
    fp=fopen("/proc/stat","r");
    fgets(state,sizeof(state),fp);
    sscanf(state,"%*s %u", &mem_use_state.memtotal);
    fgets(state,sizeof(state),fp);
    sscanf(state,"%*s %u", &mem_use_state.memfree);
    memused = (float)(mem_use_state.memtotal - mem_use_state.memfree);
    memtotal = (float)(mem_use_state.memtotal);
    rate = (memused / memtotal) * 100;
    fclose(fp);
    return rate;
}

QString get_mem_usage()
{
     QString mem_usage;
     float rate = get_mem_rate();
     mem_usage = QString("Mem usage: %1%").arg(rate);
     return mem_usage;
}

#endif // MEM_H

