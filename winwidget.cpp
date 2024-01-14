#include "winwidget.h"
#include "ui_winwidget.h"

winwidget::winwidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::winwidget)
{
    ui->setupUi(this);
}

winwidget::~winwidget()
{
    delete ui;
}
