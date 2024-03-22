#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H


#include <QtWidgets/QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QFontComboBox>
#include <QToolButton>
#include <QTextCharFormat>
#include "showwidget.h"

class ImageProcessor : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessor(QWidget *parent = nullptr);
    ~ImageProcessor();
    void createActions();   //创建动作
    void createMenus();     //创建菜单
    void createToolBars();  //创建工具栏
    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);

private:
    //各种菜单项
    QMenu* fileMenu, * zoomMenu, * rotateMenu, * mirrorMenu;
    QImage img;
    QString fileName;
    ShowWidget* showWidget;
    //文件菜单项
    QAction* openFileAction, * NewFileAction, * PrintTextAction, * PrintImageAction, * exitAction,
        * copyAction, * cutAction, * pasteAction, * aboutAction, * zoomInAction, * zoomOutAction,
        * rotate90Action, * rotate180Action, * rotate270Action, * mirrorVerticalAction,
        * mirrorHorizontalAction, * undoAction, * redoAction;
    QToolBar* fileTool, * zoomTool, * rotateTool, * mirrorTool, * doToolBar;

    QLabel * fontLabel1, * fontLabel2;
    QFontComboBox * fontComboBox;
    QComboBox * sizeComboBox;
    QToolButton * boldBtn, * italicBtn, * underlineBtn, * colorBtn;
    QToolBar * fontToolBar;

    QLabel * listLabel;
    QComboBox * listComboBox;
    QActionGroup * actGrp;
    QAction * leftAction, * rightAction, * centerAction, * justifyAction;
    QToolBar * listToolBar;
protected slots:
    void ShowNewFile();
    void ShowOpenFile();
    void ShowPrintText();
    void ShowPrintImage();
    void ShowZoomIn();
    void ShowZoomOut();
    void ShowRotate90();
    void ShowRotate180();
    void ShowRotate270();
    void ShowMirrorVertical();
    void ShowMirrorHorizontal();

    void ShowFontComboBox(QFont comboFont);
    void ShowSizeSpinBox(QString spinValue);
    void ShowBoldBtn();
    void ShowItalicBtn();
    void ShowUnderlineBtn();
    void ShowColorBtn();
    void ShowCurrentFormatChanged(const QTextCharFormat & fmt);

    void ShowList(int);
    void ShowAlignment(QAction * act);
    void ShowCursorPositionChanged();
};

#endif // IMAGEPROCESSOR_H
