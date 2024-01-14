    #include "troops.h"

    Troops::Troops(qreal cxl, qreal cyl, QGraphicsScene* scene, qreal x, qreal y, int h, int p, QVector<QPair<int,int>> *path,  QVector<Troops*>*tro, int *bulldam, int *numoftro): Object(nullptr, -1, h, p)
    {
        numoft = numoftro;
        isMarkedForDeletion = false;
        troops = tro;
        bulletDamage = bulldam;
        image1 = QPixmap(":/troopKnifeAttack1.png").scaled(p, p);
        image2 = QPixmap(":/troopKnifeAttack2.png").scaled(p, p);
        setPixmap(image1);
        collisionTimer = new QTimer(this);
        isColliding = false;
        connect(collisionTimer, &QTimer::timeout, this, &Troops::switchImage);

        // Initialize the castle position
        castlePos.setX(cxl*p);
        castlePos.setY(cyl*p);
        psize = p;
        QPixmap t(":/troopKnifeAttack1.png");
        t = t.scaled(p, p);
        setPixmap(t);
        this->scene = scene;
        scene->addItem(this);
        QPointF p5(x,y);
        setPos(p5);
       // intialize the path of the file
        for(int i = 0; i < path->size();i++)
        {
            int pathx = path->at(i).first;
            int pathy = path->at(i).second;
            pathWay.push_back(QPointF(pathx*p, pathy*p));
        }
        it = pathWay.begin();

    }
    //handles the two images for colligin
    void Troops::switchImage() {
        if (pixmap().cacheKey() == image1.cacheKey()) {
            setPixmap(image2);
        } else {
            setPixmap(image1);
        }
    }
    //delay function
    void Troops:: delay(int millisecondsToWait)
    {
        QEventLoop loop;
        QTimer::singleShot(millisecondsToWait, &loop, SLOT(quit()));
        loop.exec();
    }
    //handles the troop movement
    void Troops::move(int factor) {
        if (it == pathWay.end()) {
            return;
        }
        QPointF prevPos = pos();
        QPointF nextPos = moveFromTo(*it, factor);
        setPos(nextPos);
        QGraphicsScene* scenePtr = scene;
        if (scenePtr) {
            //handles collision with troops
            QList<QGraphicsItem *> collidingItemsList = scenePtr->collidingItems(this);
            int nonTroopCollisions = 0;
            for (QGraphicsItem *item : collidingItemsList) {
                Object* object = dynamic_cast<Object*>(item);
                if (object && object->getType() != -1 && object->getType() != 2)
                {
                    if (object->getType() == 5) {
                        this->reduceHealth(*bulletDamage);
                    }
                    object->handleCollisionWithTroops(this);
                    if (object->getType() != -1) {
                        nonTroopCollisions++;
                    }
                }
            }

            if (nonTroopCollisions > 0) {
                setPos(prevPos);
            }

            if (!isColliding && nonTroopCollisions > 0) {
                collisionTimer->start(100);
                isColliding = true;
            }

            if (isColliding && nonTroopCollisions == 0) {
                QTimer::singleShot(100, [this]() {
                    collisionTimer->stop();
                    isColliding = false;
                });
            }
        }
    }
    //reduce the health of the troops
    void Troops::reduceHealth(int k)
    {
        health -= k;
        if(health<=0)
        {
            QVector<Troops*>::iterator it = std::find(troops->begin(), troops->end(), this);
            if (it != troops->end()) {
                (*it)->hide();
                (*numoft)++;
                if((*numoft) > 40)
                    (*bulletDamage) = (*bulletDamage)*(1.1);
                isMarkedForDeletion = true;
            }
        }
    }
    //move according to dijkstra
    QPointF Troops::moveFromTo(QPointF &p2, int k)
    {
        QPointF nextPos = pos() + (p2 - pos()) / k;
        setPos(nextPos);

        if(it != pathWay.end())
        {
            if((p2 == pos()) || (p2 - pos()).manhattanLength() <= 20){
                it++;
            }
        }

        return nextPos;
    }



