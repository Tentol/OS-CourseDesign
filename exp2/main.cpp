#include "mainwindow.h"
#include <QApplication>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char *argv[])
{
    int pid1,pid2,pid3;
    while((pid1=fork())==-1);
    if (pid1==0)
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        a.exec();
    }
    else
    {
        while ((pid2=fork())==-1);
        if (pid2==0)
            {
            QApplication b(argc, argv);
            MainWindow2 x;
            x.show();
            b.exec();
            }
        else
         {
            while ((pid3=fork())==-1);
             if (pid3==0)
            {
            QApplication c(argc, argv);
            MainWindow3 y;
            y.show();
            c.exec();
        }
    }
       }
    return 0;
}
