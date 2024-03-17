#include "dialog.h"
#include <QProgressDialog>
#include <QFont>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QFont font("ZYSong18030",12);
    setFont(font);
    setWindowTitle(tr("Progress"));
    FileNum = new QLabel(tr("文件数目："));
    FileNumLineEdit = new QLineEdit(tr("100000"));
    ProgressType = new QLabel(tr("显示类型："));
    comboBox = new QComboBox;
    comboBox->addItem(tr("progressBar"));
    comboBox->addItem(tr("progressDialog"));
    progressBar = new QProgressBar;
    startBtn = new QPushButton(tr("开始"));
    mainLayout = new QGridLayout(this);
    mainLayout->addWidget(FileNum,0,0);
    mainLayout->addWidget(FileNumLineEdit,0,1);
    mainLayout->addWidget(ProgressType,1,0);
    mainLayout->addWidget(comboBox,1,1);
    mainLayout->addWidget(progressBar,2,0,1,2);
    mainLayout->addWidget(startBtn,3,1);
    mainLayout->setSpacing(10);
    connect(startBtn,SIGNAL(clicked()),this,SLOT(startProgress()));
}

Dialog::~Dialog() {}

void Dialog::startProgress(){
    bool ok;
    int num = FileNumLineEdit->text().toInt(&ok); //获取需要复制的文件数目
    if(comboBox->currentIndex() == 0){
        progressBar->setRange(0,num);
        for(int i = 1;i <= num;i++){
            progressBar->setValue(i);             //每复制完一个文件后步值数加一
        }
    }else if(comboBox->currentIndex() == 1){
        //创建一个新的进度对话框
        QProgressDialog * progressDialog = new QProgressDialog(this);
        QFont font("ZYSong18030",12);
        progressDialog->setFont(font);
        progressDialog->setWindowModality(Qt::WindowModal);  //设置进度条窗口为模态方式显示，即显示窗口时其他窗口将不响应输入信号
        progressDialog->setMinimumDuration(5);  //设置进度条对话框出现需等待的时间，默认为4秒
        progressDialog->setWindowTitle(tr("Please Wait"));
        progressDialog->setLabelText(tr("Copying..."));  //设置进度条对话框显示的文字
        progressDialog->setCancelButtonText(tr("Cancel"));
        progressDialog->setRange(0,num);
        for(int i = 1;i <= num;i++){
            progressDialog->setValue(i);
            if(progressDialog->wasCanceled()){        //检测取消按钮是否被触发
                return;
            }
        }
    }
}
