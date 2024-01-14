    #ifndef OBJECT_H
    #define OBJECT_H
    #include <QObject>
    #include <QGraphicsPixmapItem>
    class Troops;
    class Object: public QObject, public QGraphicsPixmapItem
    {
        Q_OBJECT
        int type=0;
    protected:
        int health=0;
        int TropDam = 10;
    public:
        explicit Object(QObject* parent = nullptr, int t = -100, int h = 0, int p = 60, int TropDam = 10);
        int getType();
        int getHealth();
        virtual void reduceHealth(int k);
        bool isDead();
        void setType(int t);
        void handleCollisionWithTroops(Troops* troop);
    public slots:

    };

    #endif // OBJECT_H
