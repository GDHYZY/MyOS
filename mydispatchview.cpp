#include "mydispatchview.h"
#include "ui_mydispatchview.h"
//#include <QHeaderView>

MyDispatchView::MyDispatchView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyDispatchView)
{
    if(MyDispatchMode::getInstance().Request(MyDispatchMode::getInstance().m_num,"Dispatch",WIN))
    {
        this->name = MyDispatchMode::getInstance().m_num++;
        ui->setupUi(this);
        ui->TsLabel->setText(QString("时间片: %1s").arg(TimeSlice));
        ui->WaitQueue->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->FinishQueue->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->RunQueue->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
    else
        close();
}

MyDispatchView::~MyDispatchView()
{
    delete ui;
    MyDispatchMode::getInstance().Recover(this->name);
}

void MyDispatchView::updateView()
{
    int n = MyDispatchMode::getInstance().Wait.size();
    //WaitQueue
    if(n)
        ui->WaitQueue->removeRow(n);
    else if(MyDispatchMode::getInstance().Finish.size())
        ui->WaitQueue->setRowCount(0);
    for(int i = 1;i < n; i++)
    {
        ui->WaitQueue->setRowCount(i);
        ui->WaitQueue->setItem(i-1,0,new QTableWidgetItem(QString("作业%1").arg(MyDispatchMode::getInstance().Wait[i].name)));
        ui->WaitQueue->setItem(i-1,1,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Wait[i].waittime)));
        ui->WaitQueue->setItem(i-1,2,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Wait[i].needruntime)));
        ui->WaitQueue->setItem(i-1,3,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Wait[i].hadruntime)));
        ui->WaitQueue->setItem(i-1,4,new QTableWidgetItem(MyDispatchMode::getInstance().Wait[i].othername));
    }
    //FinishQueue
    n = MyDispatchMode::getInstance().Finish.size();
    for(int i = 0;i < n; i++)
    {
        ui->FinishQueue->setRowCount(i+1);
        ui->FinishQueue->setItem(i,0,new QTableWidgetItem(QString("作业%1").arg(MyDispatchMode::getInstance().Finish[i].name)));
        ui->FinishQueue->setItem(i,1,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Finish[i].waittime)));
        ui->FinishQueue->setItem(i,2,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Finish[i].needruntime)));
        ui->FinishQueue->setItem(i,3,new QTableWidgetItem(QString::number(MyDispatchMode::getInstance().Finish[i].hadruntime)));
        ui->FinishQueue->setItem(i,4,new QTableWidgetItem(MyDispatchMode::getInstance().Finish[i].othername));
    }
    //RunQueue
    if(!MyDispatchMode::getInstance().Wait.isEmpty())
    {
        ui->RunQueue->setRowCount(1);
        ui->RunQueue->setItem(0,0,new QTableWidgetItem(QString("作业%1").arg(MyDispatchMode::getInstance().Wait[0].name)));
    }
    else if(MyDispatchMode::getInstance().Finish.size())
        ui->RunQueue->setRowCount(0);
}


void MyDispatchView::on_PushWorkbtn_clicked()
{
    MyDispatchMode::getInstance().Push();
    updateView();
}

