#include "startwidget.h"
#include "ui_startwidget.h"

Startwidget::Startwidget(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Startwidget)
{
    ui->setupUi(this);

}

Startwidget::~Startwidget()
{
    delete ui;
}

void Startwidget::on_startbutton_clicked()
{
    this->hide();
}

