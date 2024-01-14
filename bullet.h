#ifndef BULLET_H
#define BULLET_H
#include "object.h"
#include <QObject>
#include <QTimer>
#include <troops.h>
#include <QPropertyAnimation>
class Bullet :public Object
{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
    QPointF m_pos;
    QPropertyAnimation *m_animation;
    int BullMovTime;
public:
    explicit Bullet(int pixsize = 0, QPointF CanPos = QPointF(500, 500), QPointF Mous = QPointF(100,100), QVector<Troops*> *trps = nullptr, int BullMovTime = 1000);
    QVector<Troops*> *troops;
    QPointF cannonPos;
    QPointF MousePos;
    bool collidesWithEnemy();
    QPointF pos() const;
    void setPos(const QPointF &pos);
    void updateScene();
signals:
    void posChanged(QPointF pos);

};

#endif // BULLET_H
