#include "ShapeWidget.h"
#include<QMouseEvent>
#include<QPainter>
#include<QPixmap>
#include<QBitmap>

ShapeWidget::ShapeWidget(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    QPixmap pix;
    //为pix添加图片，0表示采用默认格式，后为读取图片的方式
    pix.load("312.png", 0, Qt::AvoidDither | Qt::ThresholdDither | Qt::ThresholdAlphaDither);
    resize(pix.size());
    //为空间增加一个遮罩，遮住所选区域以外的部分使其看起来透明
    setMask(QBitmap(pix.mask()));
}

ShapeWidget::~ShapeWidget()
{}

void ShapeWidget::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
    if (event->button() == Qt::RightButton) {
        close();
    }
}

void ShapeWidget::mouseMoveEvent(QMouseEvent* event) {
    if (event->buttons() & Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void ShapeWidget::paintEvent(QPaintEvent* event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, QPixmap("312.png"));
}
