#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QFrame>
#include <QPixmap>
#include <QHBoxLayout>
#include <QPushButton>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private:
    //左侧
    QLabel * UserNameLabel;
    QLabel * NameLabel;
    QLabel * SexLabel;
    QLabel * DepartmentLabel;
    QLabel * AgeLabel;
    QLabel * OtherLabel;
    QLineEdit * UserNameLineEdit;
    QLineEdit * NameLineEdit;
    QComboBox * SexComboBox;
    QTextEdit * DepartmentTextEdit;
    QLineEdit * AgeLineEdit;
    QGridLayout * LeftLayout;         //网格布局

    //右侧
    QLabel * HeadLabel;
    QLabel * HeadIconLabel;
    QPushButton * UpdateHeadBtn;
    QHBoxLayout * TopRightLayout;     //水平布局
    QLabel * IntroductionLabel;
    QTextEdit * IntroductionTextEdit;
    QVBoxLayout * RightLayout;        //垂直布局

    //底部
    QPushButton * OkBtn;
    QPushButton * CancelBtn;
    QHBoxLayout * BottomLayout;
};
#endif // DIALOG_H
