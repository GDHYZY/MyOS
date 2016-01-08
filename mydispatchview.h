#ifndef MYDISPATCHVIEW_H
#define MYDISPATCHVIEW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "mydispatchmode.h"
#include "mymemorymode.h"


namespace Ui {
class MyDispatchView;
}

class MyDispatchView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyDispatchView(QWidget *parent = 0);
    ~MyDispatchView();
    void updateView();
    int name;
signals:
    virtual void closeEvent(QCloseEvent *event);

private slots:
    void on_PushWorkbtn_clicked();


private:
    Ui::MyDispatchView *ui;
};

#endif // MYDISPATCHVIEW_H
