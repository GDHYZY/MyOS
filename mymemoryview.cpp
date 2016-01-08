#include "mymemoryview.h"
#include "ui_mymemoryview.h"

MyMemoryView::MyMemoryView(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyMemoryView)
{
    if(MyDispatchMode::getInstance().Request(MyDispatchMode::getInstance().m_num,"Memory",WIN))
    {
        this->name = MyDispatchMode::getInstance().m_num++;
        ui->setupUi(this);
        ui->progressBar->setRange(0,MAXSIZE);
        ui->progressBar_2->setRange(0,DISKMAX);
        ui->label->setText(QString("%1KB / %2KB").arg(MyMemoryMode::getInstance().m_use).arg(MAXSIZE));
        ui->label_2->setText(QString("%1KB / %2KB").arg(MyMemoryMode::getInstance().m_diskuse).arg(DISKMAX));
        ui->progressBar->setValue(MyMemoryMode::getInstance().m_use);
        ui->progressBar_2->setValue(MyMemoryMode::getInstance().m_diskuse);
    }
    else
        close();
}

MyMemoryView::~MyMemoryView()
{
    delete ui;
    MyDispatchMode::getInstance().Recover(this->name);
}

void MyMemoryView::updateView()
{
    ui->label->setText(QString("%1KB / %2KB").arg(MyMemoryMode::getInstance().m_use).arg(MAXSIZE));
    ui->label_2->setText(QString("%1KB / %2KB").arg(MyMemoryMode::getInstance().m_diskuse).arg(DISKMAX));
    ui->progressBar->setValue(MyMemoryMode::getInstance().m_use);
    ui->progressBar_2->setValue(MyMemoryMode::getInstance().m_diskuse);
}
