#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <random>
#include <QMessageBox>
#include <cmath>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("График");
    ui->doubleSpinBox_4->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    double z=(double)(rand())/RAND_MAX;
    ui->doubleSpinBox_4->setValue(z);
}


void MainWindow::on_pushButton_2_clicked()
{
    const double T=0.01;
    if (ui->doubleSpinBox_2->value()>=ui->doubleSpinBox_3->value())
    {
         QMessageBox::critical(this, "Ошибка", "Левая граница интервала больше или равна второй");
         ui->doubleSpinBox->setValue(0);
         ui->doubleSpinBox_2->setValue(0);
         ui->doubleSpinBox_3->setValue(0);
         ui->doubleSpinBox_4->setValue(0);
    }
    else if (ui->doubleSpinBox_3->value()-ui->doubleSpinBox_2->value()<T)
    {
        QMessageBox::critical(this, "Ошибка", "Длина интервала меньше периода");
        ui->doubleSpinBox->setValue(0);
        ui->doubleSpinBox_2->setValue(0);
        ui->doubleSpinBox_3->setValue(0);
        ui->doubleSpinBox_4->setValue(0);
    }
    else
    {
    ui->pushButton_3->setEnabled(true);
    double a=ui->doubleSpinBox->value();
    double xmin=ui->doubleSpinBox_2->value();
    double xmax=ui->doubleSpinBox_3->value();
    double z=ui->doubleSpinBox_4->value();
    ui->customPlot->xAxis->setRange(int(xmin), int(xmax));
    double b = (xmax-xmin)/T;
    int interval=int (b);
    double x1,y1;
    QVector <double> x;
    QVector <double> y;
    int i=0;
    while (i<interval)
    {
        y1=a*sin(pow(xmin,4))+z;
        x1=xmin;
        xmin+=T;
        x.push_back(x1);
        y.push_back(y1);
       i++;
    }
    double max=y[0];
    double min=y[0];
    for (int i=1; i<x.size(); i++)
    {
        if (y[i]>max)
        {
            max=y[i];
        }
        if (y[i]<min)
        {
            min=y[i];
        }
    }
    ui->customPlot->yAxis->setRange(max+0.5,min-0.5);
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setData(x, y);
    ui->customPlot->yAxis->setLabel("y");
    ui->customPlot->xAxis->setLabel("x");
    ui->customPlot->replot();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    ui->pushButton_3->setEnabled(false);
    ui->doubleSpinBox->setValue(0);
    ui->doubleSpinBox_2->setValue(0);
    ui->doubleSpinBox_3->setValue(0);
    ui->doubleSpinBox_4->setValue(0);
    ui->customPlot->clearGraphs();
    ui->customPlot->replot();
}

