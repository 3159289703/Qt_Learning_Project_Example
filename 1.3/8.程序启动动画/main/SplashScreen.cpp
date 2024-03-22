#include "SplashScreen.h"
#include<QTextEdit>
#include<windows.h>

SplashScreen::SplashScreen(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowTitle(tr("Splash Example"));
    QTextEdit* edit = new QTextEdit(tr("Splash Example"));
    setCentralWidget(edit);
    resize(600, 450);
    Sleep(1000);    //使程序初始化时休眠几秒
}

SplashScreen::~SplashScreen()
{}
