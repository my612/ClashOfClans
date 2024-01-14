#include "bullet.h"

Bullet::Bullet(int pixsize, QPointF CanPos, QPointF Mouse, QVector<Troops*> *trps, int BullMovTime)
    :Object(nullptr, 5,0, pixsize)
{
    this->BullMovTime = BullMovTime;
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setTransformOriginPoint(boundingRect().center());
    //start mouse pos with cannon pos
    MousePos = Mouse;
    cannonPos = CanPos;
    QPixmap t(":/tile_0005.png");
    t = t.scaled(pixsize/2, pixsize/2);
    setPixmap(t);
    setPos(cannonPos);

    // get the direction and the end position of the bullet
    QPointF direction = MousePos - cannonPos;
    double magnitude = std::sqrt(std::pow(direction.x(), 2) + std::pow(direction.y(), 2));
    direction = direction * ((1080 / magnitude));
    QPointF endPos = cannonPos + direction;
    //the animation of the bullet
    m_animation = new QPropertyAnimation(this, "pos");
    m_animation->setStartValue(cannonPos);
    m_animation->setEndValue(MousePos);
    m_animation->setDuration(BullMovTime);  // 1 second
    m_animation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(this, &Bullet::posChanged, this, &Bullet::updateScene);
    connect(m_animation, &QPropertyAnimation::finished, this, &Bullet::deleteLater);
}

QPointF Bullet::pos() const {
    return m_pos;
}


void Bullet::updateScene() {
    if(scene()) {
        scene()->update();
    }
}
//change bullet's position
void Bullet::setPos(const QPointF &pos) {
    if (pos.x() < 0 || pos.y() < 0) {
        qDebug() << "Error: Invalid position";
        return;
    }

    if (m_pos == pos)
        return;

    m_pos = pos;
    QGraphicsItem::setPos(pos);

    emit posChanged(m_pos);
}
