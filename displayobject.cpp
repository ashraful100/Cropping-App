#include "displayobject.h"
#include "ui_displayobject.h"

displayObject::displayObject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::displayObject)
{
    ui->setupUi(this);
    this->move(10,10);    
    ui->Cancel->setShortcut(QKeySequence(Qt::Key_Escape));
    ui->Save->setShortcut(QKeySequence(Qt::Key_S));
}

void displayObject::displayImage(Mat3b obj, string path, int number)
{
    toSave = obj;
    savePath = path;

    QImage img= Mat3b2QImage(obj);
    ui->label->setScaledContents(true);
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setPixmap(QPixmap::fromImage(img));    

    ui->numOfObject->setText("No. of Cropped Objects: " + QString::number(number)
                             +"(" +QString::number(obj.rows)+","+QString::number(obj.cols)+")");
}

displayObject::~displayObject()
{
    delete ui;
}

QImage displayObject::Mat3b2QImage(Mat3b src)
{    
    QImage dest(src.cols, src.rows, QImage::Format_ARGB32);
    for (int y = 0; y < src.rows; ++y) {
        const cv::Vec3b *srcrow = src[y];
        QRgb *destrow = (QRgb*)dest.scanLine(y);
        for (int x = 0; x < src.cols; ++x) {
            destrow[x] = qRgba(srcrow[x][2], srcrow[x][1], srcrow[x][0], 255);
        }
    }
    return dest;
}

int displayObject::readTextFile()
{
    QFile file("ObjectNumber.txt");

    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        return 0;
    }
    QTextStream in(&file);
    QString text = in.readAll();

    int number = text.toInt();
    number++;

    qDebug()<<number;
    return number;
}

void displayObject::writeTextFile(int num)
{
    QFile file("ObjectNumber.txt");

    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        return ;
    }
    QTextStream out(&file);
    out<<num;
    qDebug()<<num;
}

void displayObject::on_Save_clicked()
{
    int number = readTextFile();

    if(savePath.empty())
    {
        QDir dir;
        qDebug()<<dir.absolutePath();
        savePath=dir.absolutePath().toLocal8Bit().constData();
    }
    string path= savePath + "/" + to_string(number) + ".jpg";
    imwrite(path, toSave);
    writeTextFile(number);
    close();
}

void displayObject::on_Cancel_clicked()
{
    close();
}
