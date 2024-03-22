#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_SplashScreen.h"

class SplashScreen : public QMainWindow
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

private:
    Ui::SplashScreenClass ui;
};
