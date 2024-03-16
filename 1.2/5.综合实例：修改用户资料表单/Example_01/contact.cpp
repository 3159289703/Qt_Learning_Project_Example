#include "contact.h"

Contact::Contact(QWidget *parent)
    : QWidget{parent}
{
    EmailLabel = new QLabel(tr("电子邮件："));
    EmailLineEdit = new QLineEdit;
    AddrLabel = new QLabel(tr("联系地址："));
    AddrLineEdit = new QLineEdit;
    CodeLabel = new QLabel(tr("邮政编码："));
    CodeLineEdit = new QLineEdit;
    MobiTelLabel = new QLabel(tr("移动电话："));
    MobiTelLineEdit = new QLineEdit;
    MobiTelCheckBox = new QCheckBox(tr("接收留信"));
    ProTelLabel = new QLabel(tr("办公电话："));
    ProTelLineEdit = new QLineEdit;
    mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->addWidget(EmailLabel,0,0);
    mainLayout->addWidget(EmailLineEdit,0,1);
    mainLayout->addWidget(AddrLabel,1,0);
    mainLayout->addWidget(AddrLineEdit,1,1);
    mainLayout->addWidget(CodeLabel,2,0);
    mainLayout->addWidget(CodeLineEdit,2,1);
    mainLayout->addWidget(MobiTelLabel,3,0);
    mainLayout->addWidget(MobiTelLineEdit,3,1);
    mainLayout->addWidget(MobiTelCheckBox,3,2);
    mainLayout->addWidget(ProTelLabel,4,0);
    mainLayout->addWidget(ProTelLineEdit,4,1);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
}
