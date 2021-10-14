#ifndef WIDGET_H
#define WIDGET_H

#include "carthread.h"
#include <QWidget>
#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include <QSystemTrayIcon>  //系统托盘功能实现
#include <QMenu>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void update_move(int);

private:
    Ui::Widget *ui;
    QLabel* car_label;
    QImage* imag;
    QSystemTrayIcon* trayIcon;  //托盘图标
    QMenu* trayIconMenu;    //托盘菜单

    //窗口管理动作
    QAction* restoreAction; //恢复窗口
    QAction* quitAction;    //退出窗口

    carthread* car_thread;  //实例化

    int movex;
    int movey;
private slots:
    void sigincre();    //延时减小，导致速度增大
    void sigdecre();    //延时增大，导致速度减小
};

#endif // WIDGET_H
