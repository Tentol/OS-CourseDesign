# OS-CourseDesign

HUST 操作系统课程设计

实验环境:Linux 4.4.16-generic/Linux 3.16.63@Ubuntu 14.04 LTS

exp1:
要求：编一个C程序，其内容为实现文件拷贝的功能；
     通过编译内核方法，增加一个新的系统调用。
     另编写一个应用程序，调用新增加的系统调用。实现的功能是：文件拷贝；
     
     exp1.c为利用buffer实现文件拷贝代码，1.c为测试系统调用程序。



exp2:
要求：编一个C程序，其内容为分窗口同时显示三个并发进程的运行结果。要求用到Linux下的图形库。用gtk/qt实现。
     
     exp2.pro为qt程序，分3个窗口mainwindow.cpp,mainwindow2.cpp,mainwindow3.cpp实现运行结果。


exp3:
要求：掌握增加设备驱动程序的方法。通过模块方法，增加一个新的设备驱动程序，其功能可以简单实现字符设备的驱动。
     
     mydev.c为编写的字符设备驱动,利用makefile编译出mydev.ko,用insmod进行安装。


exp4:
要求：了解/proc文件的特点和使用方法，用图形界面实现系统监控状态。
     
     demo.pro为qt程序，实现了CPU，系统，内存，进程的监控。
