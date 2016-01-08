#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QCloseEvent>
#include "mydispatchview.h"
#include "mymemoryview.h"
#include "mydispatchmode.h"
#include "mymemorymode.h"
#include "myfile.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    int name;
    void Init();
    void InitConnect();
    virtual void closeEvent(QCloseEvent *e);
private slots:
    void OpenDispatch();
    void OpenMemory();
    void OpenFile();

    void deleteDispatchView();
    void deleteMemoryView();
    void deleteFile();
    void UDVM();
    void QUIT();

private:
    QPalette* m_palette;
    QPushButton* m_closebtn;
    QPushButton* m_dispatchbtn;
    QPushButton* m_memorybtn;
    QPushButton* m_filebtn;
    QTimer* m_timer;

    MyDispatchView* m_dispatch;
    MyMemoryView* m_memory;
    MyFile* m_file;
};

#endif // WIDGET_H
