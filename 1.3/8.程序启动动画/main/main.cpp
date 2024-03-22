#include "SplashScreen.h"
#include <QtWidgets/QApplication>
#include <QPixmap>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("312.png");  //设置启动图片
    QSplashScreen splash(pixmap);
    splash.show();
    a.processEvents();  //使程序显示启动动画时仍能响应鼠标等其他事件
    SplashScreen w;
    w.show();
    splash.finish(&w);
    return a.exec();
}
