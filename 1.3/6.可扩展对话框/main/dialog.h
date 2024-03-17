#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void showDetailInfo();
private:
    void createBaseInfo();    //实现基本对话框窗体部分
    void createDetailInfo();  //实现扩展窗体部分
    QWidget * baseWidget;     //基本对话框窗体部分
    QWidget * detailWidget;   //扩展窗体部分
};
#endif // DIALOG_H
