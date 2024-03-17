#ifndef DIALOG_H
#define DIALOG_H

#include <QLabel>
#include <QLineEdit>
#include <QProgressBar>
#include <QComboBox>
#include <QPushButton>
#include <QGridLayout>
#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
private slots:
    void startProgress();
private:
    QLabel * FileNum;
    QLineEdit * FileNumLineEdit;
    QLabel * ProgressType;
    QComboBox * comboBox;
    QProgressBar * progressBar;
    QPushButton * startBtn;
    QGridLayout * mainLayout;
};
#endif // DIALOG_H
