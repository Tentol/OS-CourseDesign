#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QList<float> ylist;
    QList<float> ylistM;

private:
    void Show_Hostname();
    void Show_Boottime();
    void Show_OSver();
    void Show_CPUver();
    void Add_CPU_Point(float cpu_usage);
    void Update_CPU_Line();
    void Add_Mem_Point(float cpu_usage);
    void Update_Mem_Line();



private slots:
    void Show_Runtime();
    void Show_CPU_usage();
    void Show_Mem_usage();
    void Show_Process_info();
    void Check_Process_info();
    void Kill_Process();

};

#endif // MAINWINDOW_H
