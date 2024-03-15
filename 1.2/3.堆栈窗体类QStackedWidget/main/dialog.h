#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QStackedWidget>
#include <QLabel>
#include <QHBoxLayout>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QListWidget * list;
    QStackedWidget * stack;
    QLabel * label1;
    QLabel * label2;
    QLabel * label3;
};
#endif // DIALOG_H
