#include "carthread.h"
#include <QDebug>

carthread::carthread(QObject *parent)
{
}

void carthread::run()
{
    while(1)
    {
        carmovPos(defmovex,defmovey);
        QThread::msleep(delay); //延时函数，用来调整速度，延时越小，相当于小车运动越快
//        sleep(delay);
    }
}

void carthread::carmovPos(const int &movex, const int &movey)
{
    posx+=movex;
    posy+=movey;
    qDebug()<<posx<<","<<posy;  //测试小车移动的位置输出
    if(posx >= 1200 || posy >=623)  //小车运动位置边界
    {
        posx = -200;
        posy = -89;
    }
    emit send_state(1);
}

int carthread::Getposx()
{
    return posx;
}

int carthread::Getposy()
{
    return posy;
}

int carthread::Getdefmovex()
{
    return defmovex;
}

int carthread::Getdefmovey()
{
    return defmovey;
}

void carthread::incdelay()
{
    delay -= 40;
}

void carthread::decdelay()
{
    delay += 40;
}

void carthread::setmovex(int& movex)
{
    defmovex = movex;
}

void carthread::setmovey(int& movey)
{
    defmovey = movey;
}

int carthread::Getdelay()
{
    return delay;
}

void carthread::speedreset()
{
    posx = 0;
    posy = 0;
    delay = 120;
    defmovex = 42;
    defmovey = 18;
}

//利用事件循环来进行非阻塞延时（适用于单线程UI）
//处理本线程的事件循环
//void carthread::sleep(unsigned int msec)
//{
//    QTime dieTime = QTime::currentTime().addMSecs(msec);
//    while(QTime::currentTime() < dieTime)
//    {
//        //强制进入当前线程的事件循环,这样可以把堵塞的事件都处理掉,从而避免程序卡死。
//        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
//        //如果去掉QCoreApplication::processEvents; 可以延时,但会阻塞线程
//    }
//}
