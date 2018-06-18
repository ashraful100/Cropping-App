#ifndef DISPLAYOBJECT_H
#define DISPLAYOBJECT_H

#include <QDialog>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QShortcut>
#include <opencv/highgui.h>

#include <iostream>


using namespace std;
using namespace cv;

namespace Ui {
class displayObject;
}

class displayObject : public QDialog
{
    Q_OBJECT    


public:
    explicit displayObject(QWidget *parent = 0);
    void displayImage(Mat3b obj, string path, int number);
    ~displayObject();

private slots:
    void on_Save_clicked();

    void on_Cancel_clicked();

private:
    Ui::displayObject *ui;
    QImage Mat3b2QImage (Mat3b src);
    Mat3b toSave;
    cv::String savePath;
    int readTextFile();
    void writeTextFile(int num);

};

#endif // DISPLAYOBJECT_H
