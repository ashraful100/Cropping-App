#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "QLineEdit"
#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QPainter>
#include <opencv/highgui.h>
#include <iostream>
#include <QShortcut>
#include <QObject>

#include "displayobject.h"
#include "manual.h"

using namespace cv;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);   
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString InputLine;
    QStringList list;
    QPixmap scaled;
    QImage image;
    cv::String image_path;
    int img_num;
    QDir dir;
    string savePath;
    displayObject *_object;
    int objCount = 0;

public slots:
    void slotMouseSingleClicked(QMouseEvent *mouseEvent);
    void slotMouseDoubleClicked(QMouseEvent *mouseEvent);
    void slotMouseMovedWithRightClickDown(QRect rectangle);
    void slotNewRectangleReceived(QRect rectangle);

private slots:       
    void on_actionOpen_File_triggered();
    void on_actionOpen_Folder_triggered();    
    void on_actionExit_triggered();
    void on_next_clicked();
    void on_previous_clicked();    
    void on_SelectSaveFolder_clicked();    
    void on_actionRead_Manual_triggered();
};

#endif // MAINWINDOW_H
