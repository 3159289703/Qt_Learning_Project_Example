#include "ImageProcessor.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPrintDialog>
#include <QPrinter>
#include <QApplication>
#include <QPainter>
#include <QPixmap>
#include <QColor>
#include <QColorDialog>
#include <QDebug>
#include <QActionGroup>
#include <QTextList>

ImageProcessor::ImageProcessor(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle(tr("Easy Word"));
    showWidget = new ShowWidget(this);
    setCentralWidget(showWidget);
    //在工具栏上嵌入控件
    fontLabel1 = new QLabel(tr("字体："));
    fontComboBox = new QFontComboBox;
    fontComboBox->setFontFilters(QFontComboBox::ScalableFonts);
    fontLabel2 = new QLabel(tr("字号："));
    sizeComboBox = new QComboBox;
    foreach (int size, QFontDatabase::standardSizes()) {
        sizeComboBox->addItem(QString::number(size));
    }
    boldBtn = new QToolButton;
    boldBtn->setText(tr("加粗"));
    boldBtn->setCheckable(true);
    italicBtn = new QToolButton;
    italicBtn->setText(tr("斜体"));
    italicBtn->setCheckable(true);
    underlineBtn = new QToolButton;
    underlineBtn->setText(tr("下划线"));
    underlineBtn->setCheckable(true);
    colorBtn = new QToolButton;
    colorBtn->setText(tr("颜色"));
    colorBtn->setCheckable(true);

    //排序
    listLabel = new QLabel(tr("排序"));
    listComboBox = new QComboBox;
    listComboBox->addItem("Standard");
    listComboBox->addItem("QTextListFormat::ListDisc");
    listComboBox->addItem("QTextListFormat::ListCircle");
    listComboBox->addItem("QTextListFormat::ListSquare");
    listComboBox->addItem("QTextListFormat::ListDecimal");
    listComboBox->addItem("QTextListFormat::ListLowerAlpha");
    listComboBox->addItem("QTextListFormat::ListUpperAlpha");
    listComboBox->addItem("QTextListFormat::ListLowerRoman");
    listComboBox->addItem("QTextListFormat::ListUpperRoman");

    //创建动作、菜单、工具栏函数
    createActions();
    createMenus();
    createToolBars();
    if (img.load("312.png")) {
        showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
    }

    connect(fontComboBox,&QFontComboBox::currentFontChanged,this,&ImageProcessor::ShowFontComboBox);
    connect(sizeComboBox,&QComboBox::textActivated,this,&ImageProcessor::ShowSizeSpinBox);
    connect(boldBtn,&QToolButton::clicked,this,&ImageProcessor::ShowBoldBtn);
    connect(italicBtn,&QToolButton::clicked,this,&ImageProcessor::ShowItalicBtn);
    connect(underlineBtn,&QToolButton::clicked,this,&ImageProcessor::ShowUnderlineBtn);
    connect(colorBtn,&QToolButton::clicked,this,&ImageProcessor::ShowColorBtn);
    connect(showWidget->text,&QTextEdit::currentCharFormatChanged,this,&ImageProcessor::ShowCurrentFormatChanged);

    connect(listComboBox,&QComboBox::activated,this,&ImageProcessor::ShowList);
    connect(showWidget->text->document(),&QTextDocument::undoAvailable,undoAction,&QAction::setEnabled);
    connect(showWidget->text->document(),&QTextDocument::redoAvailable,redoAction,&QAction::setEnabled);
    connect(showWidget->text,&QTextEdit::cursorPositionChanged,this,&ImageProcessor::ShowCursorPositionChanged);
}

ImageProcessor::~ImageProcessor()
{}

void ImageProcessor::createActions() {
    openFileAction = new QAction(tr("打开"), this);
    openFileAction->setShortcut(tr("Ctrl+O"));          //设置组合键
    openFileAction->setStatusTip(tr("打开一个文件"));     //设置状态栏显示
    connect(openFileAction, &QAction::triggered, this, &ImageProcessor::ShowOpenFile);

    NewFileAction = new QAction(tr("新建"), this);
    NewFileAction->setShortcut(tr("Ctrl+N"));
    NewFileAction->setStatusTip(tr("新建一个文件"));
    connect(NewFileAction, &QAction::triggered, this, &ImageProcessor::ShowNewFile);

    exitAction = new QAction(tr("退出"), this);
    exitAction->setShortcut(tr("Ctrl+Q"));
    exitAction->setStatusTip(tr("退出程序"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);

    copyAction = new QAction(tr("复制"), this);
    copyAction->setShortcut(tr("Ctrl+C"));
    copyAction->setStatusTip(tr("复制文件"));
    connect(copyAction, &QAction::triggered, showWidget->text, &QTextEdit::copy);

    cutAction = new QAction(tr("剪切"), this);
    cutAction->setShortcut(tr("Ctrl+X"));
    cutAction->setStatusTip(tr("剪切文件"));
    connect(cutAction, &QAction::triggered, showWidget->text, &QTextEdit::cut);

    pasteAction = new QAction(tr("粘贴"),this);
    pasteAction->setShortcut(tr("Ctrl+V"));
    pasteAction->setStatusTip(tr("粘贴文件"));
    connect(pasteAction, &QAction::triggered, showWidget->text, &QTextEdit::paste);

    aboutAction = new QAction(tr("关于"), this);
    connect(aboutAction, &QAction::triggered, this, &QApplication::aboutQt);

    PrintTextAction = new QAction(tr("打印文本"), this);
    PrintTextAction->setStatusTip(tr("打印一个文本"));
    connect(PrintTextAction, &QAction::triggered, this, &ImageProcessor::ShowPrintText);

    PrintImageAction = new QAction(tr("打印图片"), this);
    PrintImageAction->setStatusTip(tr("打印一张图片"));
    connect(PrintImageAction, &QAction::triggered, this, &ImageProcessor::ShowPrintImage);

    zoomInAction = new QAction(tr("放大"), this);
    zoomInAction->setStatusTip(tr("放大一幅图片"));
    connect(zoomInAction,&QAction::triggered,this,&ImageProcessor::ShowZoomIn);
    zoomOutAction = new QAction(tr("缩小"), this);
    zoomOutAction->setStatusTip(tr("缩小一幅图片"));
    connect(zoomOutAction,&QAction::triggered,this,&ImageProcessor::ShowZoomOut);

    rotate90Action = new QAction(tr("旋转90°"), this);
    rotate90Action->setStatusTip(tr("将图片旋转90°"));
    connect(rotate90Action,&QAction::triggered,this,&ImageProcessor::ShowRotate90);
    rotate180Action = new QAction(tr("旋转180°"), this);
    rotate180Action->setStatusTip(tr("将图片旋转180°"));
    connect(rotate180Action,&QAction::triggered,this,&ImageProcessor::ShowRotate180);
    rotate270Action = new QAction(tr("旋转270°"));
    rotate270Action->setStatusTip(tr("将图片旋转270°"));
    connect(rotate270Action,&QAction::triggered,this,&ImageProcessor::ShowRotate270);

    mirrorVerticalAction = new QAction(tr("纵向镜像"), this);
    mirrorVerticalAction->setStatusTip(tr("将图片纵向镜像"));
    connect(mirrorVerticalAction,&QAction::triggered,this,&ImageProcessor::ShowMirrorVertical);
    mirrorHorizontalAction = new QAction(tr("横向镜像"));
    mirrorHorizontalAction->setStatusTip(tr("将图片横向镜像"));
    connect(mirrorHorizontalAction,&QAction::triggered,this,&ImageProcessor::ShowMirrorHorizontal);
    undoAction = new QAction(tr("撤销"), this);
    connect(undoAction, &QAction::triggered, showWidget->text, &QTextEdit::undo);

    redoAction = new QAction(tr("重做"), this);
    connect(redoAction, &QAction::triggered, showWidget->text, &QTextEdit::redo);

    actGrp = new QActionGroup(this);
    leftAction = new QAction(tr("左对齐"),actGrp);
    leftAction->setCheckable(true);
    rightAction = new QAction(tr("右对齐"),actGrp);
    rightAction->setCheckable(true);
    centerAction = new QAction(tr("居中"),actGrp);
    centerAction->setCheckable(true);
    justifyAction = new QAction(tr("两端对齐"),actGrp);
    justifyAction->setCheckable(true);
    connect(actGrp,&QActionGroup::triggered,this,&ImageProcessor::ShowAlignment);
}

void ImageProcessor::createMenus() {
    fileMenu = menuBar()->addMenu(tr("文件"));
    fileMenu->addAction(openFileAction);
    fileMenu->addAction(NewFileAction);
    fileMenu->addAction(PrintTextAction);
    fileMenu->addAction(PrintImageAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    zoomMenu = menuBar()->addMenu(tr("编辑"));
    zoomMenu->addAction(copyAction);
    zoomMenu->addAction(cutAction);
    zoomMenu->addAction(pasteAction);
    zoomMenu->addAction(aboutAction);
    zoomMenu->addSeparator();
    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);
    rotateMenu = menuBar()->addMenu(tr("旋转"));
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);
    mirrorMenu = menuBar()->addMenu(tr("镜像"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);
}

void ImageProcessor::createToolBars() {
    fileTool = addToolBar("File");
    fileTool->addAction(openFileAction);
    fileTool->addAction(NewFileAction);
    fileTool->addAction(PrintTextAction);
    fileTool->addAction(PrintImageAction);
    zoomTool = addToolBar("Edit");
    zoomTool->addAction(copyAction);
    zoomTool->addAction(cutAction);
    zoomTool->addAction(pasteAction);
    zoomTool->addSeparator();
    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);
    rotateTool = addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);
    doToolBar = addToolBar("doEdit");
    doToolBar->addAction(undoAction);
    doToolBar->addAction(redoAction);

    fontToolBar = addToolBar("Font");
    fontToolBar->addWidget(fontLabel1);
    fontToolBar->addWidget(fontComboBox);
    fontToolBar->addWidget(fontLabel2);
    fontToolBar->addWidget(sizeComboBox);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(boldBtn);
    fontToolBar->addWidget(italicBtn);
    fontToolBar->addWidget(underlineBtn);
    fontToolBar->addSeparator();
    fontToolBar->addWidget(colorBtn);

    listToolBar = addToolBar("list");
    listToolBar->addWidget(listLabel);
    listToolBar->addWidget(listComboBox);
    listToolBar->addSeparator();
    listToolBar->addActions(actGrp->actions());
}

void ImageProcessor::ShowNewFile() {
    ImageProcessor* newImageProcessor = new ImageProcessor;
    newImageProcessor->show();
}

void ImageProcessor::ShowOpenFile() {
    fileName = QFileDialog::getOpenFileName(this);
    if (!fileName.isEmpty()) {
        if (showWidget->text->document()->isEmpty()) {
            loadFile(fileName);
        }
        else {
            ImageProcessor* newImageProcessor = new ImageProcessor;
            newImageProcessor->show();
            newImageProcessor->loadFile(fileName);
        }
    }
}

void ImageProcessor::loadFile(QString filename) {
    printf("file name:%s\n", filename.toUtf8().data());
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream textStream(&file);
        while (!textStream.atEnd()) {
            showWidget->text->append(textStream.readLine());
            printf("read line\n");
        }
        printf("end\n");
    }
}

void ImageProcessor::ShowPrintText() {
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()){
        QTextDocument * doc = showWidget->text->document();
        doc->print(&printer);
    }
}

void ImageProcessor::ShowPrintImage(){
    QPrinter printer;
    QPrintDialog printDialog(&printer,this);
    if(printDialog.exec()){
        QPainter painter(&printer);
        QRect rect = painter.viewport();                //获得QPainter对象的视图矩形区域
        QSize size = img.size();                        //获得图像的大小
        size.scale(rect.size(),Qt::KeepAspectRatio);    //按照图形的比例大小重新设置视图矩形区域
        painter.setViewport(rect.x(),rect.y(),size.width(),size.height());
        painter.setWindow(img.rect());                  //设置QPainter窗口大小为视图大小
        painter.drawImage(0,0,img);                     //打印图像
    }
}

void ImageProcessor::ShowZoomIn(){
    if(img.isNull()){
        return;
    }
    QTransform transform;
    transform.scale(2,2);                               //按照2倍水平垂直放大
    img = img.transformed(transform);;
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowZoomOut(){
    if(img.isNull()){
        return;
    }
    QTransform transform;
    transform.scale(0.5,0.5);                               //按照2倍水平垂直缩小
    img = img.transformed(transform);;
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowRotate90(){
    if(img.isNull()){
        return;
    }
    QTransform transform;
    transform.rotate(90);
    img = img.transformed(transform);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowRotate180(){
    if(img.isNull()){
        return;
    }
    QTransform transform;
    transform.rotate(180);
    img = img.transformed(transform);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowRotate270(){
    if(img.isNull()){
        return;
    }
    QTransform transform;
    transform.rotate(270);
    img = img.transformed(transform);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowMirrorVertical(){
    if(img.isNull()){
        return;
    }
    img = img.mirrored(false,true);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowMirrorHorizontal(){
    if(img.isNull()){
        return;
    }
    img = img.mirrored(true,false);
    showWidget->imageLabel->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessor::ShowFontComboBox(const QFont comboFont){
    QTextCursor cursor = showWidget->text->textCursor();
    QFont f = cursor.charFormat().font();
    f.setFamily(comboFont.family());
    QTextCharFormat fmt;
    fmt.setFont(f);
    // 如果光标没有高亮选区，将光标所在处的词作为选区
    if(!cursor.hasSelection()){
        cursor.select(QTextCursor::WordUnderCursor);
    }
    cursor.mergeCharFormat(fmt);
    showWidget->text->setTextCursor(cursor);
}

void ImageProcessor::ShowSizeSpinBox(QString spinValue){
    QTextCharFormat fmt;
    fmt.setFontPointSize(spinValue.toFloat());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImageProcessor::ShowBoldBtn() {
    QTextCursor cursor = showWidget->text->textCursor();
    QTextCharFormat fmt;
    if (boldBtn->isChecked()) {
        fmt.setFontWeight(QFont::Bold);
    } else {
        fmt.setFontWeight(QFont::Normal);
    }
    cursor.mergeCharFormat(fmt);
    showWidget->text->setTextCursor(cursor);
}

void ImageProcessor::ShowItalicBtn(){
    QTextCharFormat fmt;
    fmt.setFontItalic(italicBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImageProcessor::ShowUnderlineBtn(){
    QTextCharFormat fmt;
    fmt.setFontUnderline(underlineBtn->isChecked());
    showWidget->text->mergeCurrentCharFormat(fmt);
}

void ImageProcessor::ShowColorBtn(){
    QColor color = QColorDialog::getColor(Qt::red,this);
    if(color.isValid()){
        QTextCharFormat fmt;
        fmt.setForeground(color);
        showWidget->text->mergeCurrentCharFormat(fmt);
    }
}

void ImageProcessor::ShowCurrentFormatChanged(const QTextCharFormat &fmt){
    fontComboBox->setCurrentIndex(fontComboBox->findText(fmt.fontFamilies().toString()));
    sizeComboBox->setCurrentIndex(sizeComboBox->findText(QString::number(fmt.fontPointSize())));
    boldBtn->setChecked(fmt.font().bold());
    italicBtn->setChecked(fmt.fontItalic());
    underlineBtn->setChecked(fmt.fontUnderline());
}

void ImageProcessor::ShowAlignment(QAction * act){
    if(act == leftAction){
        showWidget->text->setAlignment(Qt::AlignLeft);
    }
    if(act == rightAction){
        showWidget->text->setAlignment(Qt::AlignRight);
    }
    if(act == centerAction){
        showWidget->text->setAlignment(Qt::AlignCenter);
    }
    if(act == justifyAction){
        showWidget->text->setAlignment(Qt::AlignJustify);
    }
}

void ImageProcessor::ShowCursorPositionChanged(){
    if(showWidget->text->alignment() == Qt::AlignLeft){
        leftAction->setChecked(true);
    }
    if(showWidget->text->alignment() == Qt::AlignRight){
        rightAction->setChecked(true);
    }
    if(showWidget->text->alignment() == Qt::AlignCenter){
        centerAction->setChecked(true);
    }
    if(showWidget->text->alignment() == Qt::AlignJustify){
        justifyAction->setChecked(true);
    }
}

void ImageProcessor::ShowList(int index){
    QTextCursor cursor = showWidget->text->textCursor();
    if(index != 0){
        QTextListFormat::Style style = QTextListFormat::ListDisc;
        switch(index){
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        case 7:
            style = QTextListFormat::ListLowerRoman;
            break;
        case 8:
            style = QTextListFormat::ListUpperRoman;
            break;
        }
        cursor.beginEditBlock();
        QTextBlockFormat blockFmt = cursor.blockFormat();
        QTextListFormat listFmt;
        if(cursor.currentList()){
            listFmt = cursor.currentList()->format();
        }else{
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }
        listFmt.setStyle(style);
        cursor.createList(listFmt);
        cursor.endEditBlock();
    }else{
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}
