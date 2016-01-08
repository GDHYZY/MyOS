#ifndef MYMEMORYVIEW_H
#define MYMEMORYVIEW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "mymemorymode.h"
#include "mydispatchmode.h"

namespace Ui {
class MyMemoryView;
}

class MyMemoryView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyMemoryView(QWidget *parent = 0);
    ~MyMemoryView();
    void updateView();
    int name;
signals:
    virtual void closeEvent(QCloseEvent *);
private:
    Ui::MyMemoryView *ui;
};

#endif // MYMEMORYVIEW_H
