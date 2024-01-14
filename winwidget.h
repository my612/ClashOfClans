#ifndef WINWIDGET_H
#define WINWIDGET_H

#include <QDialog>

namespace Ui {
class winwidget;
}

class winwidget : public QDialog
{
    Q_OBJECT

public:
    explicit winwidget(QWidget *parent = nullptr);
    ~winwidget();

private:
    Ui::winwidget *ui;
};

#endif // WINWIDGET_H
