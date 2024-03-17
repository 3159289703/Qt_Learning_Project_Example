#include "digiclock.h"
#include <QTimer>
#include <QTime>
#include <QMouseEvent>

DigiClock::DigiClock(QWidget * parent) : QLCDNumber(parent)
{
    //设置时钟背景
    QPalette p = palette();
    p.setColor(QPalette::Window,Qt::blue);
    setPalette(p);

    //设置窗体的标识，此处设置为一个没有面板边框和标题栏的窗体
    setWindowFlags(Qt::FramelessWindowHint);
    //设置窗体半透明
    setWindowOpacity(0.5);
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(showTime()));

    //以1000毫秒为周期启动定时器
    showTime();    //初始时间显示
    resize(150,60);    //设置电子时钟显示的尺寸
    showColon = true;    //初始化
}

void DigiClock::showTime(){
    //获取当前系统时间
    QTime time = QTime::currentTime();
    //把获取的当前时间转换为字符串类型
    QString text = time.toString("hh:mm");
    if(showColon){
        text[2] = ':';
        showColon = false;
    }else{
        text[2] = ' ';
        showColon = true;
    }
    display(text);    //显示转换好的字符串时间
}

void DigiClock::mousePressEvent(QMouseEvent * event){
    if(event->button() == Qt::LeftButton){
        dragPosition = event->globalPosition() - frameGeometry().topLeft();
                                //event->globalPosition() 返回的是 QPoint 类型，而 frameGeometry().topLeft() 返回的是 QPointF 类型
        event->accept();
    }
    if(event->button() == Qt::RightButton){
        close();
    }
}

void DigiClock::mouseMoveEvent(QMouseEvent * event){
    if(event->buttons() & Qt::LeftButton){
        move((event->globalPosition() - dragPosition).x(),(event->globalPosition() - dragPosition).y());
        event->accept();
    }
}
