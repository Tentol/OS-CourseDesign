#ifndef CPU_H
#define CPU_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <QString>
#include <QFile>
#include <QTextStream>

typedef struct CPU_USE_STATE
{
    char name[16];
    unsigned int user;
    unsigned int nice;
    unsigned int system;
    unsigned int idle;
    unsigned int iowait;
    unsigned int irq;
    unsigned int softirq;
    unsigned int guest;
}CPU_USE_STATE;

void get_cpu_usestate(CPU_USE_STATE *cpu_state)
{
    FILE *fp;
    char state[256];
    fp=fopen("/proc/stat","r");
    fgets(state,sizeof(state),fp);
    sscanf(state,"%s %u %u %u %u %u %u %u %u", cpu_state->name, &cpu_state->user, &cpu_state->nice, &cpu_state->system, &cpu_state->idle, &cpu_state->iowait, &cpu_state->irq, &cpu_state->softirq, &cpu_state->guest);
    fclose(fp);
}

unsigned long cal_total_cpu_use(CPU_USE_STATE cpu_state)
{
    unsigned long total_cpu_use;
    total_cpu_use = (unsigned long)(cpu_state.user + cpu_state.nice + cpu_state.system +cpu_state.idle +cpu_state.iowait + cpu_state.irq +cpu_state.softirq);
    return total_cpu_use;
}

float get_cpu_rate()
{
    CPU_USE_STATE cpu_state1;
    CPU_USE_STATE cpu_state2;
    unsigned long total_cpu_use1, total_cpu_use2;
    float total, idle, rate;
    get_cpu_usestate(&cpu_state1);
    usleep(400000);
    get_cpu_usestate(&cpu_state2);
    total_cpu_use1 = cal_total_cpu_use(cpu_state1);
    total_cpu_use2 = cal_total_cpu_use(cpu_state2);
    total = (float)(total_cpu_use2 - total_cpu_use1);
    idle = (float)(cpu_state2.idle - cpu_state1.idle);
    rate = ((total - idle) / total) * 100;
    return rate;
}

QString get_cpu_usage()
{
    QString cpu_usage;
    float rate = get_cpu_rate();
    cpu_usage = QString("CPU usage: %1%").arg(rate);
    return cpu_usage;
}

QString get_cpu_mhz()
{
    FILE *fp;
    QString cpu_mhz;
    float mhz;
    char info[50];
    fp = fopen("/proc/cpuinfo","r");
    for(int i = 0; i < 8; i++)
    {
        fgets(info,sizeof(info),fp);
    }

    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %*s %*s %f", &mhz);
    cpu_mhz = QString("CPU MHZ: %1 MHZ").arg(mhz);
    return cpu_mhz;

}

QString get_processor0()
{
    int i=0;
    QString processor0;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str = stream.readLine();
        if(i == 3){
            processor0 = str;
            break;
        }
        i++;
    }
    processor0 = processor0.mid(13,50);
    file.close();
    return processor0;
}

QString get_processor1()
{
    int i=0;
    QString processor1;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str = stream.readLine();
        if(i == 33){
            processor1 = str;
            break;
        }
        i++;
    }
    processor1 = processor1.mid(13,50);
    file.close();
    return processor1;
}

QString get_processor2()
{
    int i=0;
    QString processor2;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str = stream.readLine();
        if(i == 63){
            processor2 = str;
            break;
        }
        i++;
    }
    processor2 = processor2.mid(13,50);
    file.close();
    return processor2;
}

QString get_processor3()
{
    int i=0;
    QString processor3;
    QString str;
    QFile file("/proc/cpuinfo");
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str = stream.readLine();
        if(i == 93){
            processor3 = str;
            break;
        }
        i++;
    }
    processor3 = processor3.mid(13,50);
    file.close();
    return processor3;
}

#endif // CPU_H

