#include "gameover.h"
#include "ui_gameover.h"

gameover::gameover(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::gameover)
{
    ui->setupUi(this);

    ui->endgame->show();
}

gameover::~gameover()
{
    delete ui;
}
