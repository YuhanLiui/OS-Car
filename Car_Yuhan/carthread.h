#ifndef CARTHREAD_H
#define CARTHREAD_H

#include <QThread>

class carthread : public QThread
{
    Q_OBJECT //使用信号与槽函数
public:
    explicit carthread(QObject *parent = nullptr);

    virtual void run(); //线程run函数重写

//    virtual void sleep(unsigned int msec);

    void carmovPos(const int& movex,const int& movey);
    int Getposx();
    int Getposy();
    int Getdefmovex();
    int Getdefmovey();
    int Getdelay();
    void incdelay();
    void decdelay();
    void speedreset();
    void setmovex(int& movex);
    void setmovey(int& movey);

signals:
    void send_state(int state);

protected:
    unsigned int delay = 100;
private:
    int posx = 0;
    int posy = 0;
    int defmovex = 42;
    int defmovey = 18;
};

#endif // CARTHREAD_H
