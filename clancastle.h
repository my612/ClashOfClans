#ifndef CLANCASTLE_H
#define CLANCASTLE_H
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QCoreApplication>
#include "object.h"
class ClanCastle: public Object
{
     Q_OBJECT
private:
    bool iscastledestroyed=false;
public:
    explicit ClanCastle(int h, int p,int TropDam, QObject* parent = nullptr);
    void setdestroyed(bool isdestroyed);
    void reduceHealth(int k) override;

signals:
    void castleDestroyed();

private:
    QGraphicsTextItem* healthText;

};

#endif // CLANCASTLE_H
