#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Snipping App");
    this->setWindowIcon(QIcon("icon.ico"));

    ui->imgLabel->setScaledContents(true);
    ui->imgLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    ui->next->setDisabled(true);
    ui->previous->setDisabled(true);
    QDir pwd;
    savePath= pwd.absolutePath().toLocal8Bit().constData();

    QFile file("ObjectNumber.txt");
    file.open(QIODevice::WriteOnly|QIODevice::Append);
    if(file.pos()==0)
    {
        QTextStream out(&file);
        out<<0;
    }

    ui->next->setShortcut(QKeySequence(Qt::Key_Right));
    ui->previous->setShortcut(QKeySequence(Qt::Key_Left));
    ui->SelectSaveFolder->setShortcut(QKeySequence(tr ("Ctrl+s")));
    ui->actionOpen_File->setShortcut(QKeySequence(tr("Ctrl+o")));
    ui->actionOpen_Folder->setShortcut(QKeySequence(tr("Ctrl+Shift+o")));
    ui->actionExit->setShortcut(QKeySequence(Qt::Key_Escape));
}

MainWindow::~MainWindow()
{
    exit(EXIT_FAILURE);
    delete ui;
}

void MainWindow::on_actionOpen_File_triggered()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString dir1 = QFileDialog::getOpenFileName(this, tr("Open File"), "E:/MasterThesis/ImageData/TrainDataset", tr("Images (*.png *.xpm *.jpg)"));

    if(!dir1.isEmpty())
    {
        image = QImage(dir1);
        image_path = dir1.toLocal8Bit().constData();
        ui->imgLabel->setPixmap(QPixmap::fromImage(image));
        QString size = " (" + QString::number(image.width()) + "," + QString::number(image.height()) + ")";
        ui->imgName->setText("Now Displaying: " + dir1 + size);

        connect(ui->imgLabel,SIGNAL(signalMouseClicked(QMouseEvent*)),this,SLOT(slotMouseSingleClicked(QMouseEvent*)));
        connect(ui->imgLabel,SIGNAL(signalMouseDoubleClicked(QMouseEvent*)),this,SLOT(slotMouseDoubleClicked(QMouseEvent*)));

        connect(ui->imgLabel,SIGNAL(signalMouseMovedWithRightClickDown(QRect)),this,SLOT(slotMouseMovedWithRightClickDown(QRect)));
        connect(ui->imgLabel,SIGNAL(signalNewRectangle(QRect)),this,SLOT(slotNewRectangleReceived(QRect)));
    }
    ui->next->setDisabled(true);
}

void MainWindow::on_actionOpen_Folder_triggered()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString dir2 = QFileDialog::getExistingDirectory(this, tr("Open Folder"), "E:/MasterThesis/ImageData/TrainDataset",
//                                                     tr("Images (*.png *.xpm *.jpg)"),
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    if(!dir2.isEmpty())
    {
        ui->next->setDisabled(false);

        dir = QDir(dir2 + "/");
        dir.setNameFilters(QStringList()<<"*.jpg");
        list = dir.entryList();


        for (int i = 0; i < list.size(); i++)
        {
            qDebug() << dir.filePath(list.at(i));
        }
        img_num = 0;

        qDebug()<<list.size();
        image = QImage (dir.filePath(list.at(img_num)));
        image_path = dir.filePath(list.at(img_num)).toLocal8Bit().constData();

        ui->imgLabel->setPixmap(QPixmap::fromImage(image));
        QString size = " (" + QString::number(image.width()) + "," + QString::number(image.height()) + ")";
        ui->imgName->setText("Now Displaying: " + dir.filePath(list.at(img_num)) + size);
        connect(ui->imgLabel,SIGNAL(signalMouseClicked(QMouseEvent*)),this,SLOT(slotMouseSingleClicked(QMouseEvent*)));
        connect(ui->imgLabel,SIGNAL(signalMouseDoubleClicked(QMouseEvent*)),this,SLOT(slotMouseDoubleClicked(QMouseEvent*)));

        connect(ui->imgLabel,SIGNAL(signalMouseMovedWithRightClickDown(QRect)),this,SLOT(slotMouseMovedWithRightClickDown(QRect)));
        connect(ui->imgLabel,SIGNAL(signalNewRectangle(QRect)),this,SLOT(slotNewRectangleReceived(QRect)));
    }
}

void MainWindow::on_actionExit_triggered()
{
    exit(EXIT_FAILURE);
}

void MainWindow::slotMouseSingleClicked(QMouseEvent *mouseEvent)
{
    int x_co= static_cast<int>(float(mouseEvent->pos().x()) / float(ui->imgLabel->width())* float((image.width())));
    int y_co= static_cast<int>(float(mouseEvent->pos().y()) / float(ui->imgLabel->height())* float((image.height())));
    QString text;
    if (mouseEvent->button()==Qt::LeftButton)
        // If the left button of mouse is pressed,...
    {
        text="Left button clicked! x="+QString::number(x_co)+" ,y="+QString::number(y_co);
    }
    else if(mouseEvent->button()==Qt::RightButton)
        // If the right button of mouse is pressed,...
    {
        text="Right button clicked! x="+QString::number(x_co)+" ,y="+QString::number(y_co);
    }
    ui->description->setText(text);

}

void MainWindow::slotMouseDoubleClicked(QMouseEvent *mouseEvent)
{
    int x_co= static_cast<int>(float(mouseEvent->pos().x()) / float(ui->imgLabel->width())* float((image.width())));
    int y_co= static_cast<int>(float(mouseEvent->pos().y()) / float(ui->imgLabel->height())* float((image.height())));

    QString text="Mouse double clicked! x="+QString::number(x_co)+" ,y="+QString::number(y_co);
    ui->description->setText(text);
}

void MainWindow::slotMouseMovedWithRightClickDown(QRect rectangle)
{
    QString text="Drawing rectangle,...";
    scaled=(QPixmap::fromImage(image)).scaled(ui->imgLabel->width(),ui->imgLabel->height());
    ui->description->setText(text);
    QPainter paint;    
    paint.begin(&scaled);
    paint.setBrush(Qt::blue);
    paint.setPen(Qt::blue);
    paint.setOpacity(0.5); // Between 0 and 1.

    paint.drawRect(rectangle);
    paint.end();

    ui->imgLabel->setPixmap(scaled);
}

void MainWindow::slotNewRectangleReceived(QRect rectangle)
{    
    Mat image2=imread(image_path);
    int x,y,cols, rows;
    x=static_cast<int>(float(rectangle.x())/float(ui->imgLabel->width())*float(image2.cols));
    y=static_cast<int>(float(rectangle.y())/float(ui->imgLabel->height())*float(image2.rows));
    cols=static_cast<int>(float(rectangle.width())/float(ui->imgLabel->width())*float(image2.cols));
    rows=static_cast<int>(float(rectangle.height())/float(ui->imgLabel->height())*float(image2.rows));

    Rect setectedRectangle =Rect(x,y, cols, rows);
    Mat3b object = image2(setectedRectangle);

    objCount++;

    QString text="New rectangle received! x="
            +QString::number(x)+", y="
            +QString::number(y)+", Height="
            +QString::number(rows)+", Width="
            +QString::number(cols);
    scaled=(QPixmap::fromImage(image)).scaled(ui->imgLabel->width(),ui->imgLabel->height());
    ui->description->setText(text);
    QPainter paint;

    if(!object.empty())
    {
        _object= new displayObject(this);
        _object->displayImage(object,savePath, objCount);
        _object->show();
    }
    paint.begin(&scaled);
    paint.setBrush(Qt::green);
    paint.setPen(Qt::green);
    paint.setOpacity(0.4); // Between 0 and 1.

    paint.drawRect(rectangle);
    paint.end();

    ui->imgLabel->setPixmap(scaled);
}

void MainWindow::on_next_clicked()
{
    img_num++;
    qDebug()<<img_num;
    if(img_num<list.size())
    {
        image=QImage (dir.filePath(list.at(img_num)));
        ui->imgLabel->setPixmap(QPixmap::fromImage(image));
        QString size = " (" + QString::number(image.width()) + "," + QString::number(image.height()) + ")";
        ui->imgName->setText("Now Displaying: " + dir.filePath(list.at(img_num))+size);
        image_path = dir.filePath(list.at(img_num)).toLocal8Bit().constData();
        ui->previous->setDisabled(false);
        if(img_num==list.size()-1)
            ui->next->setDisabled(true);
    }
}

void MainWindow::on_previous_clicked()
{
    if(img_num>0)
    {
        ui->next->setDisabled(false);
        img_num--;
        image=QImage (dir.filePath(list.at(img_num)));
        ui->imgLabel->setPixmap(QPixmap::fromImage(image));
        QString size = " (" + QString::number(image.width()) + "," + QString::number(image.height()) + ")";
        ui->imgName->setText("Now Displaying: " + dir.filePath(list.at(img_num))+size);
        image_path = dir.filePath(list.at(img_num)).toLocal8Bit().constData();
        if(img_num==0)
            ui->previous->setDisabled(true);
    }
}

void MainWindow::on_SelectSaveFolder_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString directory = QFileDialog::getExistingDirectory(this, tr("Open Folder"),
                                                          tr("Images (*.png *.xpm *.jpg)"),
                                                          QFileDialog::ShowDirsOnly
                                                          | QFileDialog::DontResolveSymlinks);
    if(!directory.isEmpty())
    {
        savePath = directory.toLocal8Bit().constData();
    }
}

void MainWindow::on_actionRead_Manual_triggered()
{
    Manual c;
    c.setModal(true);
    c.exec();
}
