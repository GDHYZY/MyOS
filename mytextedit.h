#ifndef MYTEXTEDIT_H
#define MYTEXTEDIT_H

#include <QTextEdit>
#include <QCloseEvent>

class MyTextEdit : public QTextEdit
{
public:
    MyTextEdit();
    MyTextEdit(int _name):name(_name){}
    virtual void closeEvent(QCloseEvent *e);
    int name;
};

#endif // MYTEXTEDIT_H
