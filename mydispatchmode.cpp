#include "mydispatchmode.h"


MyDispatchMode::MyDispatchMode()
{
}

int MyDispatchMode::updateMode()
{
    int key = 0;   
    if(Wait.isEmpty())
        return 0;
    if(Wait[0].othername == "" && Wait[0].hadruntime + TimeSlice >= Wait[0].needruntime)
    {
        Wait[0].hadruntime = Wait[0].needruntime;
        Finish.append(Wait[0]);
        MyMemoryMode::getInstance().Recover(Wait[0].name);
        Wait.removeAt(0);
    }
    else
    {
        Wait[0].hadruntime += TimeSlice;
        Wait.append(Wait[0]);
        Wait.removeAt(0);
        key = 1;
    }
    int n = Wait.size();
    if(key)
        --n;
    for(int i = 0; i < n;i++)
        Wait[i].waittime += TimeSlice;
    return 1;
}

void MyDispatchMode::Push()
{
    if(MyMemoryMode::getInstance().Request(m_num,TASK))
    {
        PCB pcb(m_num++,rand()%5);
        Wait.append(pcb);
    }
}

int MyDispatchMode::Request(int name, QString otname, int type)
{
    if(MyMemoryMode::getInstance().Request(name,type))
    {
        PCB pcb(name,otname);
        Wait.append(pcb);
        return 1;
    }
    return 0;
}

void MyDispatchMode::Recover(int name)
{
    MyMemoryMode::getInstance().Recover(name);
    for(int i = 0;i < Wait.size();++i)
    {
        if(Wait[i].name == name)
        {
            Finish.append(Wait[i]);
            Wait.removeAt(i);
            return;
        }
    }
}




