#ifndef DETAIL_H
#define DETAIL_H

#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QTextEdit>
#include <QGridLayout>

class Detail : public QWidget
{
    Q_OBJECT
public:
    explicit Detail(QWidget *parent = nullptr);

signals:
private:
    QLabel * NationalLabel;
    QComboBox * NationalComboBox;
    QLabel * ProvinceLabel;
    QComboBox * ProvinceComboBox;
    QLabel * CityLabel;
    QLineEdit * CityLineEdit;
    QLabel * IntroductLabel;
    QTextEdit * IntroductTextEdit;
    QGridLayout * mainLayout;
};

#endif // DETAIL_H
