#ifndef CONTACT_H
#define CONTACT_H

#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QCheckBox>

class Contact : public QWidget
{
    Q_OBJECT
public:
    explicit Contact(QWidget *parent = nullptr);

signals:
private:
    QLabel * EmailLabel;
    QLineEdit * EmailLineEdit;
    QLabel * AddrLabel;
    QLineEdit * AddrLineEdit;
    QLabel * CodeLabel;
    QLineEdit * CodeLineEdit;
    QLabel * MobiTelLabel;
    QLineEdit * MobiTelLineEdit;
    QCheckBox * MobiTelCheckBox;
    QLabel * ProTelLabel;
    QLineEdit * ProTelLineEdit;
    QGridLayout * mainLayout;
};

#endif // CONTACT_H
