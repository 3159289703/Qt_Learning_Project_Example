#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QLineEdit>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void createCtrlFrame();    //完成窗体左半部分颜色选择区域的创建
    void createContentFrame(); //完成窗体右半部分的创建
    void fillColorList(QComboBox *);  //完成向颜色下拉列表框中插入颜色的工作
private slots:
    void ShowWindow();
    void ShowWindowText();
    void ShowButton();
    void ShowButtonText();
    void ShowBase();
private:
    //颜色选择面板
    QFrame * ctrlFrame;
    QLabel * windowLabel;
    QComboBox * windowComboBox;
    QLabel * windowTextLabel;
    QComboBox * windowTextComboBox;
    QLabel * buttonLabel;
    QComboBox * buttonComboBox;
    QLabel * buttonTextLabel;
    QComboBox * buttonTextComboBox;
    QLabel * baseLabel;
    QComboBox * baseComboBox;
    //具体显示面板
    QFrame * contentFrame;
    QLabel * label1;
    QComboBox * comboBox1;
    QLabel * label2;
    QLineEdit * lingEdit2;
    QTextEdit * textEdit;
    QPushButton * OkBtn;
    QPushButton * CancelBtn;
};
#endif // DIALOG_H
