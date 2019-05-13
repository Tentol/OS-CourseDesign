#include "mainwindow.h"
#include "ui_mainwindow3.h"
using namespace std;
MainWindow3::MainWindow3(QWidget *parent):QMainWindow(parent),ui(new Ui::MainWindow3)
{
    ui->setupUi(this);
    i=0;
    all=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(Mainnumber()));
    timer->start(1000);
}

void MainWindow3::Mainnumber()
{
    i++;
    all=all+i;
    if (i==1000)
            timer->stop();
    sprintf(string3,"%d %d",i,all);
    ui->textBrowser->append(string3);
}

MainWindow3::~MainWindow3()
{
    delete ui;
}
