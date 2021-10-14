#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    setFixedSize(1400,900);  //设置窗体大小

    QIcon icon = QIcon(":/icon/icon.png");
    setWindowIcon(icon);    //设置窗体图标
    setWindowTitle("Yuhan's car");  //设置窗体名

    car_label = new QLabel(this);  //定义小车变量为car_label

    imag = new QImage;
    imag->load(":imag/car1.png");   //导入小车实际图片
    car_label->setPixmap(QPixmap::fromImage(*imag));    //将图片加入label标签控件
    car_label->resize(200,89);  //设置car_label的大小

    car_thread = new carthread();
    car_label->move(0,0); //设置小车的初始位置

    QPushButton* increSpe = new QPushButton(this);  //加速按钮
    increSpe->move(150,700);
    increSpe->setText("小车加速");

    //将点击“加速”按钮这一事件与槽函数signicre()链接，即点击事件触发这个函数（后面同）
    connect(increSpe, &QPushButton::clicked, [=](){
        sigincre();
    });

    QPushButton* decreSpe = new QPushButton(this);  //减速按钮
    decreSpe->move(150,730);
    decreSpe->setText("小车减速");

    connect(decreSpe, &QPushButton::clicked, [=](){
        sigdecre();
    });

    QPushButton* reset = new QPushButton(this); //复位按钮
    reset->move(325,700);
    reset->setText("整体复位");

    connect(reset, &QPushButton::clicked,[=](){
        car_thread->speedreset();
    });

    QPushButton* setSpdx = new QPushButton(this);
    setSpdx->move(500,700);
    setSpdx->setText("设置x轴移速");

    QLineEdit* setSpdx_line = new QLineEdit(this);
    //由于QLineEdit默认长度不够显示提示文字，因此得自定，参数分别为x,y,width,height
    setSpdx_line->setGeometry(594,700,480,28);
    setSpdx_line->setPlaceholderText("建议填写14的整数倍且与下倍数相同以保证小车按预先设置路线移动");

    connect(setSpdx, &QPushButton::clicked, [=](){
        movex = setSpdx_line->text().toInt();
        car_thread->setmovex(movex);
    });

    QPushButton* setSpdy = new QPushButton(this);
    setSpdy->move(500,730);
    setSpdy->setText("设置y轴移速");

    QLineEdit* setSpdy_line = new QLineEdit(this);
    setSpdy_line->setGeometry(594,730,480,28);
    setSpdy_line->setPlaceholderText("建议填写6的整数倍且与上倍数相同以保证小车按预先设置路线移动");

    connect(setSpdy, &QPushButton::clicked, [=](){
        movey = setSpdy_line->text().toInt();
        car_thread->setmovey(movey);
    });

    QPushButton* exitcar = new QPushButton(this);   //实现“小车程序到后台，收纳到托盘”功能按钮
    exitcar->move(325,730);
    exitcar->setText("移至后台");

    QPushButton* shutdown = new QPushButton(this);  //退出程序按钮
    shutdown->setGeometry(1150,700,100,60);
    shutdown->setText("退出");

    connect(shutdown, &QPushButton::clicked, [=](){
        exit(0);
    });

    car_thread->start();    //线程开始（程序运行）

    //设置信号量通过run()函数发送，即run()函数调用carmovPos()发送
    //将槽函数与信号链接
    connect(car_thread,SIGNAL(send_state(int)),this,SLOT(update_move(int)));

    //托盘初始化
    trayIcon = new QSystemTrayIcon(this);

    trayIcon->setIcon(icon);    //设置托盘图标
    trayIcon->setToolTip("Yuhan's car");

    connect(exitcar, &QPushButton::clicked,[=](){
        hide();
        trayIcon->show(); //必须调用，否则托盘图标不显示
    });

    //创建菜单项动作
    restoreAction = new QAction("恢复", this);

    //此处triggered()信号是触发式信号（点击后无法切换状态，要么关要么开）
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));
    quitAction = new QAction("退出", this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit())); //关闭应用，qApp对应的是程序全局唯一指针

    //创建托盘菜单
    //必须先创建动作，后添加菜单项（不然程序会直接死掉)!!!
    QMenu* trayIconMenu = new QMenu(this);

    trayIcon->setContextMenu(trayIconMenu); //按照默认方式设置一个菜单
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();   //右键弹出来的两个选项之间加一道横线
    trayIconMenu->addAction(quitAction);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::update_move(int state)
{
    if(state)
    {
       car_label->move(car_thread->Getposx(),car_thread->Getposy()); //设置小车的初始位置
    }
}

//减小速度
void Widget::sigincre()
{
    car_thread->incdelay();
}

//增大速度
void Widget::sigdecre()
{
    car_thread->decdelay();
}
