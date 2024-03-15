#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("DockWindows"));      //设置主窗口标题栏文字
    QTextEdit * te = new QTextEdit(this);   //定义一个QTextEdit对象作为主窗口
    te->setText(tr("Main Window"));
    te->setAlignment(Qt::AlignCenter);
    setCentralWidget(te);                   //将此编辑窗口设置为主窗口的中央窗体

    //停靠窗口1
    QDockWidget * dock = new QDockWidget(tr("DockWindow1"),this);
    //可移动
    dock->setFeatures(QDockWidget::DockWidgetMovable);
                                            //Movable可移，Closable可关闭，Floatable可浮动，VerticalTitleBar在左边显示垂直的标签栏
                                            //QDockWidget::NoDockWidgetFeatures不可移动 不可关闭 不可浮动
                                            //可采用或（|）的方式对多个特性组合设定
    //可停靠区域
    dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
                                            //Left左，Right右，Top顶端，Bottom底部，All以上四个，No只可停靠在插入处
    QTextEdit * te1 = new QTextEdit();
    te1->setText(tr("Window1,dock小部件可以由用户在dock之间移动" ""));
    dock->setWidget(te1);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //停靠窗口2
    dock = new QDockWidget(tr("DockWindow2"),this);
    //可关闭，可浮动
    dock->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetFloatable);

    QTextEdit * te2 = new QTextEdit();
    te2->setText(tr("Window2,dock小部件可以从主窗口分离," "作为一个独立的窗口浮动，并且可以关闭"));
    dock->setWidget(te2);
    addDockWidget(Qt::RightDockWidgetArea,dock);

    //停靠窗口3
    dock = new QDockWidget(tr("DockWindow3"),this);
    //带垂直标签栏
    dock->setFeatures(QDockWidget::DockWidgetVerticalTitleBar);

    QTextEdit * te3 = new QTextEdit();
    te3->setText(tr("Window3,dock小部件在左侧显示一个垂直标题栏"));
    dock->setWidget(te3);
    addDockWidget(Qt::RightDockWidgetArea,dock);
}

MainWindow::~MainWindow() {}
