#ifndef MANUAL_H
#define MANUAL_H

#include <QDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class Manual;
}

class Manual : public QDialog
{
    Q_OBJECT

public:
    explicit Manual(QWidget *parent = 0);
    ~Manual();

private:
    Ui::Manual *ui;
};

#endif // MANUAL_H
