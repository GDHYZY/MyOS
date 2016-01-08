#include "mytextedit.h"
#include "mydispatchmode.h"
#include <QDebug>

MyTextEdit::MyTextEdit()
{

}

void MyTextEdit::closeEvent(QCloseEvent *e)
{
    MyDispatchMode::getInstance().Recover(name);
    qDebug() << "I leave";
    e->accept();
}

