#ifndef PROCESS_H
#define PROCESS_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <sstream>
#include <QString>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QProcess>

using namespace std;

#define MAX_LENGTH 50

typedef struct PROCESS_INFO
{
    char name[MAX_LENGTH];
    char state[MAX_LENGTH];
    unsigned int pid;
    unsigned int tgid;
    unsigned int ppid;
}PROCESS_INFO;

PROCESS_INFO get_pid_info(const char* pid)
{
    FILE *fp;
    PROCESS_INFO process_info;
    char str[20];
    char filename[MAX_LENGTH];
    char info[MAX_LENGTH];
    sprintf(filename,"/proc/%s/status",pid);
    fp = fopen(filename,"r");

    //get process name
    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %s", process_info.name);

    //get process state
    fgets(info,sizeof(info),fp);
    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %s %s", process_info.state, str);
    strcat(process_info.state, " ");
    strcat(process_info.state, str);


    //get process tgid
    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %u", &process_info.tgid);

    //get process pid
    fgets(info,sizeof(info),fp);
    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %u", &process_info.pid);

    //get process ppid
    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %u", &process_info.ppid);

    fclose(fp);
    return process_info;
}

QString get_pid_all_info(const char* pid)
{
    QString str;
    char filename[MAX_LENGTH];
    sprintf(filename,"/proc/%s/status",pid);
    QFile file(filename);
    file.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream stream(&file);
    stream.readLine();
    while(!stream.atEnd())
    {
        str += stream.readLine();
        str += QString("\n");
    }
    return str;
}

void get_process_info(unsigned int &process_num)
{
    DIR *dir;
    struct dirent *ptr;
    unsigned int num = 0;
    if(!(dir = opendir("/proc")))
        return;
    while((ptr = readdir(dir)) != false)
    {
        if(ptr->d_name[0] >= '1' && ptr->d_name[0] <= '9')
        {
            num++;
        }
    }
    process_num = num;
    closedir(dir);
    return;
}

QString get_process_info()
{
    DIR *dir;
    QString pid_info;
    PROCESS_INFO process_info;
    struct dirent *ptr;
    if(!(dir = opendir("/proc")))
        return 0;
    while((ptr = readdir(dir)) != false)
    {
        if(ptr->d_name[0] >= '1' && ptr->d_name[0] <= '9')
        {
            process_info = get_pid_info(ptr->d_name);
            pid_info += QString("  NAME:  %1          PID:  %2          TGID:  %3          PPID:  %4          STATE:  %5\n").arg(process_info.name).arg(process_info.pid).arg(process_info.tgid).arg(process_info.ppid).arg(process_info.state);
        }
    }
    closedir(dir);
    return pid_info;
}


QString check_process_info(QString input)
{
    DIR *dir;
    QString pid_info;
    PROCESS_INFO process_info;
    string name, pid;
    bool flag = false;
    struct dirent *ptr;
    if(!(dir = opendir("/proc")))
        return 0;
    while((ptr = readdir(dir)) != false)
    {
        if(ptr->d_name[0] >= '1' && ptr->d_name[0] <= '9')
        {
            process_info = get_pid_info(ptr->d_name);
            name = process_info.name;
            stringstream ss;
            ss << process_info.pid;
            pid = ss.str();
            if(input == QString::fromStdString(name) || input == QString::fromStdString(pid))
            {
                pid_info = QString("Name:   %1\n").arg(process_info.name) + get_pid_all_info(ptr->d_name);
                flag = true;
                break;
            }
        }
    }

    if(flag == false)
    {
        QMessageBox::critical(NULL, "CRITICAL", "NO PROCESS!", QMessageBox::Ok|QMessageBox::Default, 0);
    }

    closedir(dir);
    return pid_info;
}

void kill_process(QString input)
{
    DIR *dir;
    QString pid_info;
    QString sudo;
    QByteArray ba;


    PROCESS_INFO process_info;
    string name, pid;
    char* command;
    bool flag = false;
    struct dirent *ptr;
    if(!(dir = opendir("/proc")))
        return;
    while((ptr = readdir(dir)) != false)
    {
        if(ptr->d_name[0] >= '1' && ptr->d_name[0] <= '9')
        {
            process_info = get_pid_info(ptr->d_name);
            name = process_info.name;
            stringstream ss;
            ss << process_info.pid;
            pid = ss.str();
            if(input == QString::fromStdString(name))
            {
                sudo = QString("pkill %1").arg(process_info.name);
                ba = sudo.toLatin1();
                command=ba.data();
                flag = true;
                break;
            }

            else if(input == QString::fromStdString(pid))
            {
                sudo = QString("kill %1").arg(process_info.pid);
                ba = sudo.toLatin1();
                command=ba.data();
                flag = true;
                break;
            }
        }
    }

    if(flag == false)
    {
        QMessageBox::critical(NULL, "CRITICAL", "NO PROCESS!", QMessageBox::Ok|QMessageBox::Default, 0);
    }

    else
    {
        system(command);
        QMessageBox::about(NULL, "SUCCESS", "KILLED PROCESS!");
    }

    closedir(dir);
    return;
}

void create_process(QString input)
{
    QProcess *pro=new QProcess;
    pro->start(input);
}

unsigned int get_thread_amount(const char* pid)
{
    FILE *fp;
    unsigned int threads_num;
    char filename[MAX_LENGTH];
    char info[MAX_LENGTH];
    sprintf(filename,"/proc/%s/status",pid);
    fp = fopen(filename,"r");

    for(int i = 0; i < 16; i++)
    {
        fgets(info,sizeof(info),fp);
    }

    fgets(info,sizeof(info),fp);
    sscanf(info,"%*s %u", &threads_num);
    return threads_num;

}

void get_threads_info(unsigned int &thread_num)
{
    DIR *dir;
    struct dirent *ptr;
    unsigned int num = 0;
    if(!(dir = opendir("/proc")))
        return;
    while((ptr = readdir(dir)) != false)
    {
        if(ptr->d_name[0] >= '1' && ptr->d_name[0] <= '9')
        {

            num += get_thread_amount(ptr->d_name);
        }
    }
    thread_num = num;
    closedir(dir);
    return;
}

#endif // PROCESS_H

