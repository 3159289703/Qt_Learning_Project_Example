#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("StackedWidget"));
    list = new QListWidget(this);         //创建一个QListWidget对象
    //在list控件中插入三个条目作为选择项
    list->insertItem(0,tr("Window1"));
    list->insertItem(1,tr("Window2"));
    list->insertItem(2,tr("Window3"));

    //创建三个QLabel控件作为堆栈窗口需要显示的三层窗体
    label1 = new QLabel(tr("WindowText1"));
    label2 = new QLabel(tr("WindowText2"));
    label3 = new QLabel(tr("WindowText3"));
    stack = new QStackedWidget(this);     //新建一个QStackedWidget堆栈体对象

    //将创建的三个QLabel控件插入堆栈窗体中
    stack->addWidget(label1);
    stack->addWidget(label2);
    stack->addWidget(label3);

    //对整个对话框进行布局
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->setSpacing(5);            //设置各个控件间距为5
    mainLayout->addWidget(list);
    mainLayout->addWidget(stack,0,Qt::AlignHCenter);
    mainLayout->setStretchFactor(list,1); //设置可伸缩控件，第一个参数指定设置的控件，第二个参数值大于0表示可伸缩
    mainLayout->setStretchFactor(stack,3);
    connect(list,SIGNAL(currentRowChanged(int)),stack,SLOT(setCurrentIndex(int)));
                                          //currentRowChanged(int)这个信号会传递一个整数参数，表示新选中的页面的索引
                                          //调用setCurrentIndex(int index)，QStackedWidget会切换到与指定索引对应的页面，并隐藏其他所有页面
}

Dialog::~Dialog() {}
