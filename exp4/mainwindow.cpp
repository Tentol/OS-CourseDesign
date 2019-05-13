#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "system.h"
#include "cpu.h"
#include "mem.h"
#include "process.h"
#include "string.h"
#include <stdio.h>
#include <QString>
#include <QTimer>
#include <QStringList>
#include <QPainter>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("proc");
    QTimer *timer_run = new QTimer(this);
    QTimer *timer_cpu = new QTimer(this);
    QTimer *timer_mem = new QTimer(this);
    QTimer *timer_process = new QTimer(this);
    Show_Hostname();
    Show_Boottime();
    Show_OSver();
    Show_CPUver();
    Show_Process_info();
    Add_CPU_Point(0);
    Update_CPU_Line();
    Add_CPU_Point(0);
    Update_CPU_Line();
    connect(timer_run, SIGNAL(timeout()), this, SLOT(Show_Runtime()));
    connect(timer_cpu, SIGNAL(timeout()), this, SLOT(Show_CPU_usage()));
    connect(timer_mem, SIGNAL(timeout()), this, SLOT(Show_Mem_usage()));
    connect(timer_process, SIGNAL(timeout()), this, SLOT(Show_Process_info()));
    connect(ui->refresh_button, SIGNAL(clicked()), this, SLOT(Show_Process_info()));
    connect(ui->check_button, SIGNAL(clicked()), this, SLOT(Check_Process_info()));
    connect(ui->kill_button, SIGNAL(clicked()), this, SLOT(Kill_Process()));
    timer_run->start(1000);
    timer_cpu->start(1000);
    timer_mem->start(2000);
    timer_process->start(30000);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Show_Hostname()
{
    QString hostname = get_hostname();
    ui->host_name->setText(hostname);
}

void MainWindow::Show_Runtime()
{
    QString runtime = get_run_time();
    ui->run_time->setText(runtime);
}

void MainWindow::Show_Boottime()
{
    QString bootTime = get_boot_time();
    ui->boot_time->setText(bootTime);
}

void MainWindow::Show_OSver()
{
    QString osversion = get_os_type();
    ui->os_version->setText(osversion);
}

void MainWindow::Show_CPUver()
{
    QString processor0 = get_processor0();
    ui->processor1->setText(processor0);
    QString processor1 = get_processor1();
    ui->processor2->setText(processor1);
    QString processor2 = get_processor2();
    ui->processor3->setText(processor2);
    QString processor3 = get_processor3();
    ui->processor4->setText(processor3);
}

void MainWindow::Show_CPU_usage()
{
    QString cpu_usage = get_cpu_usage();
    ui->cpu_usage->setText(cpu_usage);
    QString cpu_mhz = get_cpu_mhz();
    ui->cpu_mhz->setText(cpu_mhz);

    unsigned int process_amount;
    get_process_info(process_amount);
    QString amount = QString("Process amount: %1").arg(process_amount);
    ui->process_amount->setText(amount);
    unsigned int threads_amount;
    get_process_info(threads_amount);
    QString amountT = QString("Threads amount: %1").arg(threads_amount);
    ui->threads_amount->setText(amountT);
    float rate = get_cpu_rate();
    Add_CPU_Point(rate);
    Update_CPU_Line();
}



void MainWindow::Show_Mem_usage()
{
    QString mem_usage = get_mem_usage();
    ui->mem_usage->setText(mem_usage);
    float rate = get_mem_rate();
    Add_Mem_Point(rate);
    Update_Mem_Line();
}

void MainWindow::Show_Process_info()
{
    QString process_info = get_process_info();
    QFont font;
    font.setPointSize(16);
    ui->process_info->setText(process_info);
    ui->process_info->setFont(font);
}

void MainWindow::Check_Process_info()
{
    QString input;
    QString process_info;
    input = ui->process_input->text();
    process_info = check_process_info(input);
    QFont font;
    font.setPointSize(16);
    ui->process_output->setText(process_info);
    ui->process_output->setFont(font);
}

void MainWindow::Kill_Process()
{
    QString input;
    input = ui->process_input->text();
    kill_process(input);
}

void MainWindow::Add_CPU_Point(float cpu_usage)
{
    int i;
    int size = ylist.size();
    if(size == 60)
    {
        ylist.pop_front();
    }
    if(size == 0)
    {
        for(i = 0; i < 59; i++)
        {
            ylist.push_back(0);
        }
    }

     ylist.push_back(cpu_usage);

}
void MainWindow::Update_CPU_Line()
{
    int count = 0;
    QPixmap pix(1080, 390);
    QPainter painter(&pix);
    QPainterPath path;
    pix.fill(Qt::gray);
    QPen pen0;
    pen0.setColor(Qt::lightGray);
    painter.setPen(pen0);
    for(int i = 1; i < 4; i++)
    {
        painter.drawLine(QPointF(0,i*97.5), QPointF(1080,i*97.5));
    }
    QPen pen;
    pen.setColor(QColor(255,140,0));
    pen.setWidth(2);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor(255,165,0));
    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);
    QPolygonF pts;
    while(count < ylist.size()-1)
    {
       pts.push_back(QPointF(18*count, 390));
       pts.push_back(QPointF(18*count, 390-3.9*(ylist.value(count))));
       pts.push_back(QPointF(18*(count+1), 390-3.9*(ylist.value(count+1))));
       pts.push_back(QPointF(18*(count+1), 390));
       count++;
    }
    path.addPolygon(pts);
    painter.drawPath(path);
    ui->cpu_line->setPixmap(pix);
}

void MainWindow::Add_Mem_Point(float mem_usage)
{
    int i;
    int size = ylistM.size();
    if(size == 60)
    {
        ylistM.pop_front();
    }
    if(size == 0)
    {
        for(i = 0; i < 59; i++)
        {
            ylistM.push_back(0);
        }
    }

     ylistM.push_back(mem_usage);

}
void MainWindow::Update_Mem_Line()
{
    int count = 0;
    QPixmap pix(1080, 390);
    QPainterPath path;
    QPainter painter(&pix);
    pix.fill(Qt::gray);
    QPen pen0;
    pen0.setColor(Qt::lightGray);
    painter.setPen(pen0);
    for(int i = 1; i < 4; i++)
    {
        painter.drawLine(QPointF(0,i*97.5), QPointF(1080,i*97.5));
    }
    QPen pen;
    pen.setColor(QColor(160,32,240));
    pen.setWidth(2);
    painter.setPen(pen);
    QBrush brush;
    brush.setColor(QColor(147,112,219));
    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);
    QPolygonF pts;
    while(count < (ylistM.size()-1))
    {
       pts.push_back(QPointF(18*count, 390));
       pts.push_back(QPointF(18*count, 390-3.9*(ylistM.value(count))));
       pts.push_back(QPointF(18*(count+1), 390-3.9*(ylistM.value(count+1))));
       pts.push_back(QPointF(18*(count+1), 390));
       count++;
    }
    path.addPolygon(pts);
    painter.drawPath(path);
    ui->mem_line->setPixmap(pix);
}

