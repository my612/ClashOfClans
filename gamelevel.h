#ifndef GAMELEVEL_H
#define GAMELEVEL_H
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "object.h"
#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QBrush>
#include <QImage>
#include <QApplication>
#include <random>
#include<QLabel>
#include <QVector>
#include <QPair>
#include <QMouseEvent>
#include "bullet.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include <vector>
#include "fence.h"
#include "troops.h"
#include "clancastle.h"
#include "cannon.h"
#include "gameover.h"
#include <QtMath>
#include"troops.h"
//#include <QSoundEffect>
#include <QCursor>
#include <QQueue>
#include <QMap>
#include <QTimeLine>
#include <queue>
class GameLevel : public QGraphicsView
{
    Q_OBJECT
    QVector<QVector<int>> Grid;
    int TroopStep = 200;
    int BulletDamage = 10;
    int respwanRate=1000;
    int FenceHealth = 1000;
    int TroopHealth = 1000;
    int CastleHealth = 2000;
    int CannonHealth = 1000;
    int TroopMovTime = 100;
    int TroopDamage = 10;
    int BulletMovTime = 1000;
    int castleIndX=0;
    int castleIndY=0;
    int canindx=0;
    int canindy=60;
    QPointF mousePos;
    QPointF CannonPos;
    bool played = false;
    bool pressed = false;
    int pixMapDim=0;
    QMap<QPair<int,int>, int> weights;
    QGraphicsScene* scene;
    int numOfTroopsDead = 0;
    QVector<QVector<Object*>> ObjectsGrid;
    QVector<Troops*> Troopss;
    QTimer *timer;  // Declare timer here

    QTimer* countdownTimer;
    QGraphicsTextItem* countdownText;
    int remainingTime; // in seconds

public:
    bool over();
    explicit GameLevel(QWidget* parent = nullptr, int TroopStep = 200, int bulld = 10, int rrate = 100, int FenHel = 1000, int TroHel = 1000, int CasHel = 2000, int CanHel = 1000, int TroopMovementTime = 100, int TroopDam = 10, int BulletMovTime = 1000);
    void updateGame();
    void GetData();
    void renderData();
    void renderIndex(int x, int y);
    void delay(int millisecondsToWait);
    QVector<QPair<int, int>> dijkstra(QVector<QVector<int>> &grid, QPair<int,int> start, QPair<int,int> end);
    ~GameLevel();
    void start();
private slots:
     void updateCountdown();

public slots:
    void onCastleDestroyed();
    void spawnTroops();
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;
signals:
};

#endif // GAMELEVEL_H
