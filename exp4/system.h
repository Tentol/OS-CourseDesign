#ifndef SYSTEM_H
#define SYSTEM_H

#include "string.h"
#include <stdio.h>
#include <stdlib.h>
#include <QString>

#define TYPE_LENGTH 50

QString get_hostname()
{
    FILE* fp;
    char host[TYPE_LENGTH];
    char *hostname;
    QString qstring_hostname = "Host name: ";
    hostname=(char*)malloc(TYPE_LENGTH*sizeof(char));
    fp=fopen("/proc/sys/kernel/hostname","r");
    fgets(host,sizeof(host),fp);
    sscanf(host,"%s",hostname);
    qstring_hostname += QString(hostname);
    fclose(fp);
    return qstring_hostname;
}

QString get_run_time()
{
    FILE* fp;
    char runtime[TYPE_LENGTH];
    float time;
    QString run_time = "Run time: ";
    fp = fopen("/proc/uptime","r");
    fgets(runtime,sizeof(runtime),fp);
    sscanf(runtime,"%f",&time);
    run_time += QString("%1 %2").arg(time).arg("s");
    fclose(fp);
    return run_time;
}

QString get_boot_time()
{
    FILE* fp;
    struct tm *ptm = NULL;
    char runtime[TYPE_LENGTH];
    float time_f;
    time_t cur_time = 0;
    time_t boot_time = 0;
    time_t run_time;
    QString week[7] = {"Sun.","Mon.","Tues.","Wed.","Thur.","Fri.","Sat."};
    QString bootTime = "Boot time: ";
    fp = fopen("/proc/uptime","r");
    fgets(runtime,sizeof(runtime),fp);
    sscanf(runtime,"%f",&time_f);
    run_time = (time_t)time_f;
    time(&cur_time);
    boot_time = cur_time - run_time;
    ptm = localtime(&boot_time);
    bootTime += QString("%1-%2-%3 %4:%5:%6 %7").arg(ptm->tm_year+1900).arg(ptm->tm_mon+1).arg(ptm->tm_mday).arg(ptm->tm_hour).arg(ptm->tm_min).arg(ptm->tm_sec).arg(week[ptm->tm_wday]);
    return bootTime;
}

QString get_os_type()
{
    QString os = "OS version: ";
    char ostype[TYPE_LENGTH],osrelease[TYPE_LENGTH];
    char buff1[TYPE_LENGTH],buff2[TYPE_LENGTH];
    FILE *fp1,*fp2;
    fp1=fopen("/proc/sys/kernel/ostype","r");
    fp2=fopen("/proc/sys/kernel/osrelease","r");
    fgets(buff1,sizeof(buff1),fp1);
    fgets(buff2,sizeof(buff2),fp2);
    sscanf(buff1,"%s",ostype);
    sscanf(buff2,"%s",osrelease);
    os += QString("%1 %2").arg(ostype).arg(osrelease);
    fclose(fp1);
    fclose(fp2);
    return os;
}

#endif // SYSTEM_H

