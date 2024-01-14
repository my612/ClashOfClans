#include "fence.h"

Fence::Fence(int h, int p, QMap<QPair<int,int>, int> *weights, int indx, int indy, int TropDam)
    : Object(nullptr, 1, h, p, TropDam)
{
    QPixmap tr(":/fence2.png");
    tr = tr.scaled(p, p);
    setPixmap(tr);
    this -> weights = weights;
    x_ind = indx;
    y_ind = indy;
}
//handle the weight of the fence according to its health
void Fence::reduceHealth(int k)
{
    health-=k;
    (*weights)[qMakePair(x_ind, y_ind)] = health;
}
