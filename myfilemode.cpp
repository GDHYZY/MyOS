#include "myfilemode.h"

MyFileMode::MyFileMode()
{

}

int MyFileMode::CreateFile(QString _nickname, int nsize)
{
    if(MyMemoryMode::getInstance().DRequest(MyDispatchMode::getInstance().m_num,nsize))
    {
        //创建图形
        //增加文件
        FileHead.append(File(_nickname,MyDispatchMode::getInstance().m_num,nsize));
        ++MyDispatchMode::getInstance().m_num;
        return 1;
    }
    return 0;
}

int MyFileMode::DeleteFile(int _name)
{
    int n = MyDispatchMode::getInstance().Wait.size();
    for(int i = 0 ; i < n;++i)
    {
        if(MyDispatchMode::getInstance().Wait[i].name == _name)
            return 0;
    }
    MyDispatchMode::getInstance().Recover(_name);
    MyMemoryMode::getInstance().DRecover(_name);
    for(int i = 0 ;i < FileHead.size();++i)
    {
        if(FileHead[i].name == _name)
        {
            FileHead.removeAt(i);
            return 1;
        }
    }
    return 0;
}

int MyFileMode::RunFile(int _name)
{
    int i;
    for(i = 0;i < FileHead.size();++i)
        if(FileHead[i].name == _name)
            break;
    return MyDispatchMode::getInstance().Request(_name,FileHead[i].nickname,FileHead[i].size);
}

