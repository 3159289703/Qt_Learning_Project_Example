#pragma once

#include <QtWidgets/QWidget>
#include "ui_ShapeWidget.h"

class ShapeWidget : public QWidget
{
    Q_OBJECT

public:
    ShapeWidget(QWidget *parent = nullptr);
    ~ShapeWidget();

private:
    Ui::ShapeWidgetClass ui;

protected:
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
private:
    QPoint dragPosition;
};
