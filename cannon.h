#ifndef CANNON_H
#define CANNON_H
#include <QGraphicsSceneMouseEvent>
#include <QApplication>
#include <QEvent>
#include <QtMath>
#include <QObject>
#include "object.h"
class Cannon :public Object
{
    Q_OBJECT  // Include the Q_OBJECT macro

private:
    bool isMoving = false;  // Add a new private member
public:
    Cannon(int h, int p, int TropDam);  // Add a QObject parent parameter
};

#endif // CANNON_H
