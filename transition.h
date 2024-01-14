#ifndef TRANSITION_H
#define TRANSITION_H

#include <QDialog>

namespace Ui {
class transition;
}

class transition : public QDialog
{
    Q_OBJECT

public:
    explicit transition(QWidget *parent = nullptr);
    ~transition();

private:
    Ui::transition *ui;
};

#endif // TRANSITION_H
