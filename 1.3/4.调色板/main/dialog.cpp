#include "dialog.h"
#include <QHBoxLayout>
#include <QGridLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    createCtrlFrame();
    createContentFrame();
    QHBoxLayout * mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(ctrlFrame);
    mainLayout->addWidget(contentFrame);
}

Dialog::~Dialog() {}

void Dialog::createCtrlFrame(){
    ctrlFrame = new QFrame;
    windowLabel = new QLabel(tr("QPalette::Window："));
    windowComboBox = new QComboBox;
    fillColorList(windowComboBox);    //向下拉列表中插入各种不同的颜色选项
    connect(windowComboBox,SIGNAL(activated(int)),this,SLOT(ShowWindow()));

    windowTextLabel = new QLabel(tr("QPalette::WindowText："));
    windowTextComboBox = new QComboBox;
    fillColorList(windowTextComboBox);
    connect(windowTextComboBox,SIGNAL(activated(int)),this,SLOT(ShowWindowText()));

    buttonLabel = new QLabel(tr("QPalette::Button："));
    buttonComboBox = new QComboBox;
    fillColorList(buttonComboBox);
    connect(buttonComboBox,SIGNAL(activated(int)),this,SLOT(ShowButton()));

    buttonTextLabel = new QLabel(tr("QPalette::ButtonText："));
    buttonTextComboBox = new QComboBox;
    fillColorList(buttonTextComboBox);
    connect(buttonTextComboBox,SIGNAL(activated(int)),this,SLOT(ShowButtonText()));

    baseLabel = new QLabel(tr("QPalette::Base："));
    baseComboBox = new QComboBox;
    fillColorList(baseComboBox);
    connect(baseComboBox,SIGNAL(activated(int)),this,SLOT(ShowBase()));

    QGridLayout * mainLayout = new QGridLayout(ctrlFrame);
    mainLayout->setSpacing(20);
    mainLayout->addWidget(windowLabel,0,0);
    mainLayout->addWidget(windowComboBox,0,1);
    mainLayout->addWidget(windowTextLabel,1,0);
    mainLayout->addWidget(windowTextComboBox,1,1);
    mainLayout->addWidget(buttonLabel,2,0);
    mainLayout->addWidget(buttonComboBox,2,1);
    mainLayout->addWidget(buttonTextLabel,3,0);
    mainLayout->addWidget(buttonTextComboBox,3,1);
    mainLayout->addWidget(baseLabel,4,0);
    mainLayout->addWidget(baseComboBox,4,1);
}

void Dialog::createContentFrame(){
    contentFrame = new QFrame;
    label1 = new QLabel(tr("请选择一个值："));
    comboBox1 = new QComboBox;
    label2 = new QLabel(tr("请输入字符串："));
    lingEdit2 = new QLineEdit;
    textEdit = new QTextEdit;
    QGridLayout * TopLayout = new QGridLayout;
    TopLayout->addWidget(label1,0,0);
    TopLayout->addWidget(comboBox1,0,1);
    TopLayout->addWidget(label2,1,0);
    TopLayout->addWidget(lingEdit2,1,1);
    TopLayout->addWidget(textEdit,2,0,1,2);
    OkBtn = new QPushButton(tr("确认"));
    CancelBtn = new QPushButton(tr("取消"));
    QHBoxLayout * BottomLayout = new QHBoxLayout;
    BottomLayout->addStretch(1);    //添加一个可伸缩空间
    BottomLayout->addWidget(OkBtn);
    BottomLayout->addWidget(CancelBtn);
    QVBoxLayout * mainLayout = new QVBoxLayout(contentFrame);
    mainLayout->addLayout(TopLayout);
    mainLayout->addLayout(BottomLayout);
}

void Dialog::ShowWindow(){
    //获取当前选择的颜色值
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[windowComboBox->currentIndex()]);
    //获得右部窗体调色板的信息
    QPalette p = contentFrame->palette();
    //设置contentFrame窗体的背景色，第一个参数为颜色主题，第二个参数为具体的颜色值
    p.setColor(QPalette::Window,color);
    //把修改后的调色板信息应用到contentFrame窗体中，更新显示
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Dialog::ShowWindowText(){
    QStringList colorList = QColor::colorNames();
    QColor color = colorList[windowTextComboBox->currentIndex()];
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::WindowText,color);
    contentFrame->setPalette(p);
}

void Dialog::ShowButton(){
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Button,color);
    contentFrame->setPalette(p);
    contentFrame->update();
}

void Dialog::ShowButtonText(){
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[buttonTextComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::ButtonText,color);
    contentFrame->setPalette(p);
}

void Dialog::ShowBase(){
    QStringList colorList = QColor::colorNames();
    QColor color = QColor(colorList[baseComboBox->currentIndex()]);
    QPalette p = contentFrame->palette();
    p.setColor(QPalette::Base,color);
    contentFrame->setPalette(p);
}

void Dialog::fillColorList(QComboBox * comboBox){
    QStringList colorList = QColor::colorNames();
    QString color;
    //对颜色列表进行遍历
    foreach(color,colorList){
        QPixmap pix(QSize(70,20));      //新建显示颜色的图标
        pix.fill(QColor(color));
        //向conboBox中插入pix
        comboBox->addItem(QIcon(pix),NULL);
        comboBox->setIconSize(QSize(70,20));
        //设置下拉列表框的尺寸调整策略为AdjustToContents（符合内容的大小）
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
    }
}
