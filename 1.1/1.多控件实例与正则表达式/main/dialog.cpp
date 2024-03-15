#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QRegularExpression regExp("[A-Za-z][1-9][0-9]{0,2}");  //正则表达式限制输入字元的范围
                                                              //第一个字元为大小写字母，后面接非0数字，再接0~2位可为0的数字
    ui->lineEdit->setValidator(new QRegularExpressionValidator(regExp,this));
    connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_lineEdit_textChanged(){
    ui->okButton->setEnabled(ui->lineEdit->hasAcceptableInput()); //当lineEdit中正确输入数据后，OK按钮将变为可用
}
