#ifndef MYDISPATCHMODE_H
#define MYDISPATCHMODE_H
#include <QList>

#include "mymemorymode.h"

#define TimeSlice 1                  //时间片

class MyDispatchMode
{
private:
    MyDispatchMode();
    MyDispatchMode(const MyDispatchMode&);
    MyDispatchMode & operator = (const MyDispatchMode&);
public:
    static MyDispatchMode & getInstance()
    {
        static MyDispatchMode m_instance;
        return m_instance;
    }

    class PCB
    {
    public:
        int name;                       //进程名
        double needruntime;             //需要运行时间
        double hadruntime;              //已运行时间
        double waittime;                //等待时间
        QString othername;              //占用文件名
        PCB(){}
        PCB(int _name,QString other):
            name(_name),needruntime(0),hadruntime(0),waittime(0),othername(other){}
        PCB(int _name,double _nt):
            name(_name),needruntime(_nt),hadruntime(0),waittime(0),othername(""){}
    };
    QList<PCB> Wait;                //等待队列
    QList<PCB> Block;               //阻塞队列
    QList<PCB> Finish;              //完成队列
    int m_num = 0;                  //分配到的ID
    int updateMode();               //时间片更新
    void Push();                    //增加作业

    int Request(int name,QString otname,int type);  //申请作业
    void Recover(int name);                         //结束作业
};

#endif // MYDISPATCHMODE_H
