#include "mainwindow.h"

#include <QApplication>
#include <QSplitter>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFont font("ZYSong18030",12);  //设置字体
    a.setFont(font);

    //分割主窗口
    QSplitter * splitterMain = new QSplitter(Qt::Horizontal,0);
                                   //设定此分割窗口为水平分割窗口
    QTextEdit * textLeft = new QTextEdit(QObject::tr("Left Widget"),splitterMain);
                                   //新建一个QTextEdit对象并插入主分割窗口中
    textLeft->setAlignment(Qt::AlignCenter);
                                   //设置textLeft的文字对齐方式  Center为居中，Left左，Right右，Up顶端，Bottom底部

    //右分割窗口
    QSplitter * splitterRight = new QSplitter(Qt::Vertical,splitterMain);
    splitterRight->setOpaqueResize(false);
                                   //设置分割窗口的分隔条在拖拽时是否实时更新，默认为true
    QTextEdit * textUp = new QTextEdit(QObject::tr("Top Widget"),splitterRight);
    textUp->setAlignment(Qt::AlignCenter);
    QTextEdit * textBottom = new QTextEdit(QObject::tr("Bottom Widget"),splitterRight);
    textBottom->setAlignment(Qt::AlignCenter);

    //设定可伸缩控件
    splitterMain->setStretchFactor(1,1);
    //第一个参数指定控件序号，从插入顺序按0开始，第二个参数大于0时可伸缩

    splitterMain->setWindowTitle(QObject::tr("Splitter"));

    // MainWindow w;
    // w.show();
    splitterMain->show();
    return a.exec();
}
