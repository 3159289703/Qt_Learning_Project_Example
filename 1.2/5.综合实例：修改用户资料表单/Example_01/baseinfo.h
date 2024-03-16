#ifndef BASEINFO_H
#define BASEINFO_H

#include <QLabel>
#include <QLineEdit>
#include <QComboBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QPushButton>

class BaseInfo : public QWidget
{
    Q_OBJECT
public:
    explicit BaseInfo(QWidget *parent = nullptr);

signals:
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
};

#endif // BASEINFO_H
