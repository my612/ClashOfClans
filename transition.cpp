#include "transition.h"
#include "ui_transition.h"

transition::transition(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::transition)
{
    ui->setupUi(this);
}

transition::~transition()
{
    delete ui;
}
