#ifndef MYFILE_H
#define MYFILE_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QList>
#include "mydispatchmode.h"
#include "mymemorymode.h"
#include "myfilemode.h"

namespace Ui {
class MyFile;
}

class MyFile : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyFile(QWidget *parent = 0);
    ~MyFile();
signals:
    virtual void closeEvent(QCloseEvent *);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

public:
    int name;
    void updateView();
private:
    Ui::MyFile *ui;
};


#endif // MYFILE_H
