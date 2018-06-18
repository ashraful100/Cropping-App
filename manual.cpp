#include "manual.h"
#include "ui_manual.h"

Manual::Manual(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manual)
{
    ui->setupUi(this);
    this->setWindowTitle("Manual");

    //Opening the About text file
    QFile file("Manual.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        QMessageBox::information(0,"Info",file.errorString());
    }
    QTextStream In(&file);
    //Setting text of About in our text browser
    ui->teManual->setText(In.readAll());
}

Manual::~Manual()
{
    delete ui;
}
