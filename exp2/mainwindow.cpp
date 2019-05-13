#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(MainWindowtm()));
    timer->start(1000);
}

void MainWindow::MainWindowtm()
{
    time(&now);
    timenow=localtime(&now);
    ui->textBrowser->append(asctime(timenow));
}

MainWindow::~MainWindow()
{
    delete ui;
}

