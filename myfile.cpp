#include "myfile.h"
#include "ui_myfile.h"
#include "mytextedit.h"
#include <QMessageBox>
#include <QDebug>

MyFile::MyFile(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyFile)
{
    if(MyDispatchMode::getInstance().Request(MyDispatchMode::getInstance().m_num,"File",WIN))
    {
        this->name = MyDispatchMode::getInstance().m_num++;
        ui->setupUi(this);
        QValidator* validator = new QIntValidator(1,DISKMAX);
        ui->filesize->setValidator(validator);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);       //选择行为，以行为单位
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);      //选择单行
    }
    else
        close();
}

MyFile::~MyFile()
{
    delete ui;
    MyDispatchMode::getInstance().Recover(this->name);
}


void MyFile::on_pushButton_clicked()
{
    int S = ui->filesize->text().toInt();
    if(S < DISKMAX/2 && ui->filename->text() != "")
    {
        if(MyFileMode::getInstance().CreateFile(ui->filename->text(),S))
            updateView();
        else
            QMessageBox::critical(this, tr("拒绝创建"), tr("磁盘容量不足"),QMessageBox::Ok);
    }
}


void MyFile::updateView()
{
    int n = MyFileMode::getInstance().FileHead.size();
    ui->tableWidget->setRowCount(n);
    for(int i = 0;i < n;++i)
    {
        ui->tableWidget->setItem(i,0,new QTableWidgetItem(MyFileMode::getInstance().FileHead[i].nickname));
        ui->tableWidget->setItem(i,1,new QTableWidgetItem(QString("%1KB").arg(MyFileMode::getInstance().FileHead[i].size)));
        ui->tableWidget->setItem(i,2,new QTableWidgetItem(QString::number(MyFileMode::getInstance().FileHead[i].name)));
    }
}



void MyFile::on_pushButton_2_clicked()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count)
    {
        int NAME = items[2]->text().toInt();
        if(MyFileMode::getInstance().RunFile(NAME))
        {
            MyTextEdit* edit = new MyTextEdit(NAME);
            edit->setWindowFlags(Qt::WindowStaysOnTopHint);
            edit->setText(items[0]->text());
            edit->show();
            updateView();
        }
        return;

    }
}

void MyFile::on_pushButton_3_clicked()
{
    QList<QTableWidgetItem*>items = ui->tableWidget->selectedItems();
    int count = items.count();
    if(count)
    {
        int NAME = items[2]->text().toInt();
        if(MyFileMode::getInstance().DeleteFile(NAME))
            updateView();
        return;
    }
}
