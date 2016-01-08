#include "mymemorymode.h"

MyMemoryMode::MyMemoryMode()
{
}

int MyMemoryMode::_request(MyMemoryMode::Room *head, int name, int nsize, int *remsize)
{
    while (head)
    {
        if (head->statue == Free && head->Size >= nsize)
        {
            head->statue = Busy;
            head->name = name;
            if (head->Size - nsize > 0)
            {
                Room* ls = new Room();
                ls->Size = head->Size - nsize;
                ls->Position = head->Position + nsize;
                ls->statue = Free;
                if (head->last)
                {
                    ls->last = head->last;
                    head->last->front = ls;
                }
                else
                    ls->last = NULL;

                head->last = ls;
                ls->front = head;
            }
            head->Size = nsize;
            break;
        }
        head = head->last;
    }
    if (head == NULL)
        return 0;
    *remsize += nsize;
    return 1;
}

void MyMemoryMode::_recover(MyMemoryMode::Room *head, int name,int* remsize)
{
    Room* p = NULL;
    while (head)
    {
        if (head->statue == Busy && head->name == name)
        {
            p = head;
            break;
        }
        head = head->last;
    }

    if (p)
    {
        *remsize -= p->Size;
        if ((p->last && p->last->statue == Free) && (p->front && p->front->statue == Busy))      //后接空闲区
        {
            p->statue = Free;
            p->name = -1;
            p->Size += p->last->Size;
            if(p->last->last)
                p->last->last->front = p;
            p = p->last;
            p->front->last = p->last;
            delete p;
            p = NULL;
        }
        else if ((p->front && p->front->statue == Free) && (p->last && p->last->statue == Busy))  //前接空闲区
        {
            p->name = -1;
            p->front->Size += p->Size;
            p->front->last = p->last;
            if(p->last)
                p->last->front = p->front;
            delete p;
            p = NULL;
        }
        else if ((p->last &&p->last->statue == Free) && (p->front && p->front->statue == Free))               //前后接空闲区
        {
            p->name = -1;
            p->front->Size += (p->Size + p->last->Size);
            p->front->last = p->last->last;
            if(p->last->last)
                p->last->last->front = p->front;
            delete p->last;
            delete p;
            p->last = NULL;
            p = NULL;
        }
        else
        {
            p->statue = Free;
            p->name = -1;
        }
    }
}

int MyMemoryMode::Request(int name, int nsize)
{
    return _request(pre,name,nsize,&m_use);
}

void MyMemoryMode::Recover(int name)
{
    _recover(pre,name,&m_use);
}

int MyMemoryMode::DRequest(int name, int nsize)
{
    return _request(disk,name,nsize,&m_diskuse);
}

void MyMemoryMode::DRecover(int name)
{
    _recover(disk,name,&m_diskuse);
}


