#ifndef STARTWIDGET_H
#define STARTWIDGET_H

#include <QDialog>

namespace Ui {
class Startwidget;
}

class Startwidget : public QDialog
{
    Q_OBJECT

public:
    explicit Startwidget(QWidget *parent = nullptr);
    ~Startwidget();

private slots:
    void on_startbutton_clicked();

private:
    Ui::Startwidget *ui;
};

#endif // STARTWIDGET_H
