#include "mainwindow.h"
#include "ui_mainwindow2.h"
using namespace std;
MainWindow2::MainWindow2(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow2)
{
    ui->setupUi(this);
    i=0;
    connect(timer,SIGNAL(timeout()),this,SLOT(Mainclrcle()));
    timer->start(1000);
}

void MainWindow2::Mainclrcle()
{
    i=i%10;
    sprintf(string2,"%d",i);
    ui->textBrowser->append(string2);
    i++;
}

MainWindow2::~MainWindow2()
{
    delete ui;
}
