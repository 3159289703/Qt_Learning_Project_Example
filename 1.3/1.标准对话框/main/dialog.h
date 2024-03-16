#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QFileDialog>
#include <QFrame>
#include <QColorDialog>
#include <QFontDialog>
#include <QMessageBox>
#include "inputdlg.h"
#include "msgboxdlg.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    //文件
    QPushButton * fileBtn;
    QLineEdit * fileLineEdit;
    QGridLayout * mainLayout;

    //颜色
    QPushButton * colorBtn;
    QFrame * colorFrame;

    //字体
    QPushButton * fontBtn;
    QLineEdit * fontLineEdit;

    //标准输入对话框
    QPushButton * inputBtn;
    InputDlg * inputDlg;

    //消息对话框
    QPushButton * MsgBtn;
    MsgBoxDlg * msgDlg;

    //自定义消息框
    QPushButton * CustomBtn;
    QLabel * label;

public slots:
    //文件
    void showFile();

    //颜色
    void showColor();

    //字体
    void showFont();

    //输入
    void showInputDlg();

    //消息对话框
    void showMsgDlg();

    //自定义消息框
    void showCustomDlg();
};
#endif // DIALOG_H
