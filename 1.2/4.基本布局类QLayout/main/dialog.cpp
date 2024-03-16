#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("UserInfo"));

    //左侧
    UserNameLabel = new QLabel(tr("用户名："));
    UserNameLineEdit = new QLineEdit;
    NameLabel = new QLabel(tr("姓名："));
    NameLineEdit = new QLineEdit;
    SexLabel = new QLabel(tr("性别："));
    SexComboBox = new QComboBox;
    SexComboBox->addItem(tr("女"));
    SexComboBox->addItem(tr("男"));
    DepartmentLabel = new QLabel(tr("部门："));
    DepartmentTextEdit = new QTextEdit;
    AgeLabel = new QLabel(tr("年龄："));
    AgeLineEdit = new QLineEdit;
    OtherLabel = new QLabel(tr("备注："));
    OtherLabel->setFrameStyle(QFrame::Panel|QFrame::Sunken);
                                    //设置控件的风格，由形状和阴影两部分配合，
                                    //形状：NoFarme,Panel,Box,HLine,VLine,WinPanel；阴影：Plain,Raised,Sunken
    LeftLayout = new QGridLayout(); //左部布局，由于此布局管理器不是主布局管理器，所以不用指定父窗口
    //向布局中添加控件
    LeftLayout->addWidget(UserNameLabel,0,0);  //用户名
    LeftLayout->addWidget(UserNameLineEdit,0,1);
    LeftLayout->addWidget(NameLabel,1,0);      //姓名
    LeftLayout->addWidget(NameLineEdit,1,1);
    LeftLayout->addWidget(SexLabel,2,0);
    LeftLayout->addWidget(SexComboBox,2,1);
    LeftLayout->addWidget(DepartmentLabel,3,0);
    LeftLayout->addWidget(DepartmentTextEdit,3,1);
    LeftLayout->addWidget(AgeLabel,4,0);
    LeftLayout->addWidget(AgeLineEdit,4,1);
    LeftLayout->addWidget(OtherLabel,5,0,1,2);
    LeftLayout->setColumnStretch(0,1);
    LeftLayout->setColumnStretch(1,3);         //设定两列分别占用空间的比例，1:3

    //右侧
    HeadLabel = new QLabel(tr("头像："));
    HeadIconLabel = new QLabel;
    QPixmap icon("312.png");
    HeadIconLabel->setPixmap(icon);
    HeadIconLabel->resize(icon.width(),icon.height());
    UpdateHeadBtn = new QPushButton(tr("更新"));
    TopRightLayout = new QHBoxLayout();
    TopRightLayout->setSpacing(20);            //设置各个控件之间的间距为20
    TopRightLayout->addWidget(HeadLabel);
    TopRightLayout->addWidget(HeadIconLabel);
    TopRightLayout->addWidget(UpdateHeadBtn);

    //右下角
    IntroductionLabel = new QLabel(tr("个人说明："));
    IntroductionTextEdit = new QTextEdit;
    RightLayout = new QVBoxLayout();
    RightLayout->addLayout(TopRightLayout);
    RightLayout->addWidget(IntroductionLabel);
    RightLayout->addWidget(IntroductionTextEdit);

    //底部
    OkBtn = new QPushButton(tr("确定"));
    CancelBtn = new QPushButton(tr("取消"));
    BottomLayout = new QHBoxLayout();
    BottomLayout->addStretch();                //在按钮之前插入一个占位符，使两个按钮能够靠右对齐并在对话框大小发生改变时按钮大小不变
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);

    //主布局
    QGridLayout * mainLayout = new QGridLayout(this);  //指定父窗口
    mainLayout->setSpacing(10);
    mainLayout->addLayout(LeftLayout,0,0);
    mainLayout->addLayout(RightLayout,0,1);
    mainLayout->addLayout(BottomLayout,1,0,1,2);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);  //设置最优显示，用户无法改变对话框大小。最优显示即空间按其sizeHint()的大小显示

}

Dialog::~Dialog() {}
