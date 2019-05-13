#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <cstdio>
#include<iostream>

namespace Ui {
class MainWindow;
class MainWindow2;
class MainWindow3;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void MainWindowtm();
private:
    Ui::MainWindow *ui;
    time_t now;
    struct tm *timenow;
    QTimer *timer =new QTimer(this);
};

class MainWindow2: public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow2(QWidget *parent = 0);
    ~MainWindow2();
public slots:
    void Mainclrcle();
private:
    Ui::MainWindow2 *ui;
    int i;
    char string2[10];
    QTimer *timer=new QTimer(this);

};

class MainWindow3 : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow3(QWidget *parent = 0);
    ~MainWindow3();
public slots:
    void Mainnumber();
private:
    Ui::MainWindow3 *ui;
    int i,all;
    char string3[10];
    QTimer *timer=new QTimer(this);
};


#endif // MAINWINDOW_H
