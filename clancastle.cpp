#include "clancastle.h"

ClanCastle::ClanCastle(int h, int p, int TropDam, QObject* parent)
    : Object(parent, 3, h, p, TropDam)
{
    QPixmap t(":/castle1.png");
    t = t.scaled(p*3, p*2.5);
    setPixmap(t);


    // Initialize healthText
    healthText = new QGraphicsTextItem();
    healthText->setPlainText(QString::number(health));

    // Add healthText to the scene
//    scene->addItem(healthText);


}
//handles the health of the castle and emits a slot once it is destroyed
void ClanCastle::reduceHealth(int k)
{
    health-=k;
    if (health <= 0) {
        emit castleDestroyed();
    }
}
