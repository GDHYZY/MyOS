#ifndef MYFILEMODE_H
#define MYFILEMODE_H
#include "mydispatchmode.h"
#include "mymemorymode.h"

class MyFileMode
{
private:
    MyFileMode();
    MyFileMode(const MyFileMode&);
    MyFileMode & operator = (const MyFileMode&);
public:
    static MyFileMode & getInstance()
    {
        static MyFileMode instance;
        return instance;
    }

    class File
    {
    public:
        QString nickname;
        int name;
        int size;
        File(){}
        File(QString nn,int n,int ss)
            :nickname(nn),name(n),size(ss){}
    };
public:
    QList<File> FileHead;
    int CreateFile(QString _nickname, int nsize);
    int DeleteFile(int _name);
    int RunFile(int _name);
};

#endif // MYFILEMODE_H
