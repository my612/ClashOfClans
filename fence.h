#ifndef FENCE_H
#define FENCE_H
#include "object.h"
class Fence: public Object
{
    QMap<QPair<int,int>, int> *weights;
    int x_ind;
    int y_ind;
public:
    Fence(int h, int p, QMap<QPair<int,int>, int> *weights, int indx, int indy, int TroDam);
    void reduceHealth(int k) override;
};

#endif // FENCE_H
