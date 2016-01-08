#ifndef MYMEMORYMODE_H
#define MYMEMORYMODE_H

#include <iostream>

#define Free 'F'
#define Busy 'B'
const int DISKMAX = 640;        //最大硬盘
const int MAXSIZE = 256;        //最大内存
const int OS = 32;              //系统消耗
const int WIN = 8;              //窗口消耗
const int TASK = 4;             //任务消耗

class MyMemoryMode
{
private:
    MyMemoryMode();
    MyMemoryMode(const MyMemoryMode&);
    MyMemoryMode & operator = (const MyMemoryMode&);
public:
    static MyMemoryMode & getInstance()
    {
        static MyMemoryMode instance;
        return instance;
    }

    class Room
    {
    public:
        char statue;
        int Size;
        int name;
        int Position;
        Room* front;
        Room* last;
        Room(){}
        Room(int pos,int size)
            :statue(Free),Size(size),name(-1),Position(pos),front(NULL),last(NULL){}
    };
    Room* pre = new Room(0,MAXSIZE);
    Room* disk = new Room(0,DISKMAX);
    int m_use = 0;
    int m_diskuse = 0;
    int Request(int name,int nsize);
    void Recover(int name);

    int DRequest(int name,int nsize);
    void DRecover(int name);
private:
    int _request(Room* head, int name, int nsize, int* remsize);
    void _recover(Room* head, int name, int* remsize);
};

#endif // MYMEMORYMODE_H
