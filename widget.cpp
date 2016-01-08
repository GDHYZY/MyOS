#include "widget.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QFile>
#include <QMessageBox>

Widget::Widget(QWidget *parent):QWidget(parent)
{
    if(MyDispatchMode::getInstance().Request(MyDispatchMode::getInstance().m_num,"YOS",OS))
    {
        this->name = MyDispatchMode::getInstance().m_num++;
        Init();
        InitConnect();
    }
    else
        close();
}

Widget::~Widget()
{

    delete m_closebtn;
    delete m_dispatchbtn;
    delete m_memorybtn;
    delete m_filebtn;
    delete m_palette;
    if(m_dispatch)
        delete m_dispatch;
    if(m_memory)
        delete m_memory;
    if(m_file)
        delete m_file;
    delete m_timer;
    MyDispatchMode::getInstance().Recover(this->name);
}

void Widget::Init()
{
    srand(0);
    this->resize(QApplication::desktop()->size());
    m_palette = new QPalette();
    m_palette->setBrush(QPalette::Window,
                      QBrush(QPixmap(":/image/BG")));
    this->setPalette(*m_palette);
    setWindowFlags(Qt::FramelessWindowHint);    //取消边框

    m_timer = new QTimer(this);
    m_timer->start(TimeSlice * 1000);

    m_closebtn = new QPushButton(this);
    m_closebtn->setGeometry(10,700,50,50);
    m_closebtn->setIcon(QIcon(":/image/CLOSE"));
    m_closebtn->setIconSize(m_closebtn->size());
    m_closebtn->setFlat(true);  //隐藏边框
    m_closebtn->setFocusPolicy(Qt::NoFocus);    //隐藏虚框
//    m_closebtn->setStyleSheet("border-radius:5px;border-width:0px;");//背景透明

    m_dispatchbtn = new QPushButton(this);
    m_dispatchbtn->setGeometry(10,100,50,50);
    m_dispatchbtn->setIcon(QIcon(":/image/DISPATCH"));
    m_dispatchbtn->setIconSize(m_dispatchbtn->size());
    m_dispatchbtn->setFlat(true);  //隐藏边框
    m_dispatchbtn->setFocusPolicy(Qt::NoFocus);    //隐藏虚框
//    m_dispatchbtn->setStyleSheet("border-radius:5px;border-width:0px;");//背景透明

    m_memorybtn = new QPushButton(this);
    m_memorybtn->setGeometry(10,200,50,50);
    m_memorybtn->setIcon(QIcon(":/image/MEMORY"));
    m_memorybtn->setIconSize(m_memorybtn->size());
    m_memorybtn->setFlat(true);  //隐藏边框
    m_memorybtn->setFocusPolicy(Qt::NoFocus);    //隐藏虚框
//    m_memorybtn->setStyleSheet("border-radius:5px;border-width:0px;");//背景透明

    m_filebtn = new QPushButton(this);
    m_filebtn->setGeometry(10,10,50,50);
    m_filebtn->setIcon(QIcon(":/image/COMPUTER"));
    m_filebtn->setIconSize(m_filebtn->size());
    m_filebtn->setFlat(true);  //隐藏边框
    m_filebtn->setFocusPolicy(Qt::NoFocus);    //隐藏虚框
//    m_filebtn->setStyleSheet("border-radius:5px;border-width:0px;");//背景透明

    m_memory = NULL;
    m_dispatch = NULL;
    m_file = NULL;
}

void Widget::InitConnect()
{
    connect(m_closebtn,SIGNAL(clicked()),this,SLOT(QUIT()));
    connect(m_dispatchbtn,SIGNAL(clicked()),this,SLOT(OpenDispatch()));
    connect(m_memorybtn,SIGNAL(clicked()),this,SLOT(OpenMemory()));
    connect(m_filebtn,SIGNAL(clicked()),this,SLOT(OpenFile()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(UDVM()));
}

void Widget::closeEvent(QCloseEvent *e)
{
    if(m_dispatch)
        delete m_dispatch;
    if(m_memory)
        delete m_memory;
    if(m_file)
        delete m_file;
    e->accept();
}

void Widget::OpenDispatch()
{
    if(m_dispatch==NULL)
    {
        m_dispatch = new MyDispatchView();
        connect(m_dispatch,MyDispatchView::closeEvent,this,Widget::deleteDispatchView);
        m_dispatch->setWindowFlags(Qt::WindowStaysOnTopHint);
        m_dispatch->show();
    }
}

void Widget::OpenMemory()
{
    if(m_memory==NULL)
    {
        m_memory = new MyMemoryView();
        connect(m_memory,MyMemoryView::closeEvent,this,Widget::deleteMemoryView);
        m_memory->setWindowFlags(Qt::WindowStaysOnTopHint);
        m_memory->show();
    }
}

void Widget::OpenFile()
{
    if(m_file==NULL)
    {
        m_file = new MyFile();
        connect(m_file,MyFile::closeEvent,this,Widget::deleteFile);
        m_file->setWindowFlags(Qt::WindowStaysOnTopHint);
        m_file->show();
    }
}

void Widget::deleteDispatchView()
{
    delete m_dispatch;
    m_dispatch = NULL;
}

void Widget::deleteMemoryView()
{
    delete m_memory;
    m_memory = NULL;
}

void Widget::deleteFile()
{
    delete m_file;
    m_file = NULL;
}

void Widget::UDVM()
{
    if(MyDispatchMode::getInstance().updateMode());
    {
        if(m_dispatch)
            m_dispatch->updateView();
        if(m_file)
            m_file->updateView();
        if(m_memory)
            m_memory->updateView();
    }

}

void Widget::QUIT()
{
    QMessageBox msgBox;
    msgBox.setText(tr("是否关闭系统?"));
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    msgBox.setWindowFlags(Qt::WindowStaysOnTopHint);
    int ret = msgBox.exec();
    if(ret == QMessageBox::Yes)
        close();
}

