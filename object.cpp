#include "object.h"
#include "troops.h"
Object::Object(QObject* parent, int t, int h, int p, int TropDam) : QObject{parent}
{
    type = t;
    health = h;
    this->TropDam = TropDam;
}

int Object::getType()
{
    return type;
}
void Object::setType(int t)
{
    type = t;
}
int Object:: getHealth()
{
    return health;
}
void Object::reduceHealth(int k)
{
    health -= k;
}
bool Object::isDead()
{
    return health <= 0;
}
void Object::handleCollisionWithTroops(Troops* troop) {
    if(this->getType()==5)
    {
        scene()->removeItem(this);
        this->deleteLater();
    }
    else if(this->getType()!=5)
    {
        this->reduceHealth(TropDam);
        if (this->health <= 0) {
            scene()->removeItem(this);
            this->deleteLater();
        }
    }
}

