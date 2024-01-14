#ifndef TROOPS_H
#define TROOPS_H
#include <QObject>
#include<cmath>
#include "object.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QApplication>
#include <QPropertyAnimation>
#include <QEventLoop>

class Troops: public Object
{
    Q_OBJECT

    Q_PROPERTY(QPointF pos READ pos WRITE setPos NOTIFY posChanged)
    int psize;
    QPointF castlePos;
    QVector<QPointF> pathWay;
    QVector<QPointF>::iterator it ;
    QPixmap image1;
    int *bulletDamage;
    QPixmap image2;
    int *numoft;
    QVector<Troops*>*troops;
    QTimer* collisionTimer;
    bool isColliding;
public:
    bool isMarkedForDeletion;
    void move(int k);
    void reduceHealth(int k);
    QPointF pos() const { return QGraphicsItem::pos(); }
    void setPos(const QPointF& newPos) { QGraphicsItem::setPos(newPos); emit posChanged(); }
    QGraphicsScene* scene;
    void delay(int millisecondsToWait);
    QPointF moveFromTo(QPointF &p2, int k);
    explicit Troops(qreal cxl = 0, qreal cyl = 0, QGraphicsScene* scene = nullptr, qreal x = 0, qreal y = 0, int h = 0, int p = 60, QVector<QPair<int, int>> *path = nullptr, QVector<Troops*>*tro  = nullptr, int *bulldam = nullptr, int *numoftro = nullptr);
signals:

    void posChanged();
public slots:
    void switchImage();

};

#endif // TROOPS_H
