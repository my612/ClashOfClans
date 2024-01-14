#include "cannon.h"

Cannon::Cannon(int h, int p, int TropDam) :Object(nullptr, 3, h, p, TropDam)
{
    QPixmap t(":/cannon.png");
    t = t.scaled(p, p);
    setPixmap(t);
}
