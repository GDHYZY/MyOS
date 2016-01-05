#include "widget.h"
#include "ui_widget.h"
#include <QDesktopWidget>
#include <QFile>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    //ui->setupUi(this);
    this->resize(QApplication::desktop()->size());
    palette = new QPalette();
    palette->setBrush(QPalette::Window,
                      QBrush(QPixmap(":/image/BG")));
    this->setPalette(*palette);
    setWindowFlags(Qt::FramelessWindowHint);    //取消边框

    pushbutton = new QPushButton(this);
    pushbutton->setGeometry(0,0,50,50);
    pushbutton->setIcon(QIcon(":/image/CLOSE"));
    pushbutton->setIconSize(pushbutton->size());
    pushbutton->setFlat(true);  //隐藏边框
    pushbutton->setFocusPolicy(Qt::NoFocus);    //隐藏虚框
    //背景透明
    pushbutton->setStyleSheet("QPushButton{border-radius:5px;border-width:0px;}");

    connect(pushbutton,SIGNAL(clicked()),this,SLOT(close()));
}

Widget::~Widget()
{
    delete ui;
}
