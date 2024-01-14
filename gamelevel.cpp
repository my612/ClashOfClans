#include "gamelevel.h"



GameLevel::GameLevel(QWidget* parent, int TroopStep, int bulld, int rrate, int FenHel, int TroHel, int CasHel, int CanHel, int TroopMovementTime, int TroopDam, int BulletMovTime) : QGraphicsView(parent)
{
    setMouseTracking(true);
    srand(time(0));
    this->TroopStep = TroopStep;
    BulletDamage = bulld;
    respwanRate = rrate;
    FenceHealth = FenHel;
    TroopHealth = TroHel;
    CastleHealth = CasHel;
    CannonHealth = CanHel;
    TroopMovTime = TroopMovementTime;
    TroopDamage = TroopDam;
    this->BulletMovTime = BulletMovTime;
    scene = new QGraphicsScene();
    this->setBackgroundBrush(QBrush(QImage(":/grass03.png")));
    GetData();
    ObjectsGrid.resize(Grid.size());
    for(int i = 0; i < Grid.size(); i++)
    {
        ObjectsGrid[i].resize(Grid[i].size());
    }
    pixMapDim = 720 / Grid.size();
    renderData();
    connect(ObjectsGrid[castleIndX][castleIndY], SIGNAL(castleDestroyed()), this, SLOT(onCastleDestroyed()));
    this->setScene(scene);
    this->setSceneRect(0, 0, 1080, 720);


    // Initialize remainingTime to 5 minutes
    remainingTime = 5 * 60;


    // Initialize countdownText
    countdownText = new QGraphicsTextItem();
    countdownText->setPlainText(QString::number(remainingTime));

    // Add countdownText to the scene
    scene->addItem(countdownText);

    // Initialize countdownTimer
    countdownTimer = new QTimer(this);
    connect(countdownTimer, &QTimer::timeout, this, &GameLevel::updateCountdown);
}
//start the game logic
void GameLevel:: start()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(spawnTroops()));
    timer->start(respwanRate);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameLevel::updateGame);
    timer->start(TroopMovTime);

    // Start the countdown timer to tick every second
    countdownTimer->start(1000);
}


void GameLevel::updateCountdown() {
    remainingTime--;

    int minutes = remainingTime / 60;
    int seconds = remainingTime % 60;

    countdownText->setHtml(QString("<font color=\"red\" size=\"14\">Remaining time: %1:%2</font>")
                               .arg(minutes, 2, 10, QChar('0')) // format minutes with leading zeros
                               .arg(seconds, 2, 10, QChar('0'))); // format seconds with leading zeros

//    if (remainingTime <= 0) {
//        countdownTimer->stop();
//        // Handle end of level
//    }
}
//show gameover window if castle destroyed
void GameLevel::onCastleDestroyed() {
    this->close();
    gameover* gove = new gameover();
    gove->show();
}
//read data from the file
void GameLevel::GetData()
{
    std::ifstream in;
   char temp;
    in.open("B:\\Fall 23\\Milestone2 - CS project\\Milestone2 - CS project\\ClashOfClans8\\ClashOfClans8\\ClashOfClans\\text\\input.txt");

    QVector<int> tempData;
    while(in.get(temp))
    {
        if(isdigit(temp))
        {
            tempData.push_back(temp - '0');
        }
        else if(temp == '\n')
        {
            Grid.push_back(tempData);
            tempData.clear();
        }
    }
    if (!tempData.empty()) {
        Grid.push_back(tempData);
    }
    in.close();
}
//updates the movement of the troops and delete them
void GameLevel:: updateGame() {
    for (auto it = Troopss.begin(); it != Troopss.end();) {
        if ((*it)->isMarkedForDeletion) {
            delete *it;
            it = Troopss.erase(it);
        } else {
            ++it;
        }
    }
    for (auto& troop : Troopss) {

        troop->move(TroopStep);
    }

}
//renders the read data into the array and sets the pixs
void GameLevel:: renderIndex(int x, int y)
{

    if(Grid[x][y] == 1)//fence
    {
        ObjectsGrid[x][y] = new Fence(FenceHealth, pixMapDim, &weights, x, y, TroopDamage);
        weights[qMakePair(x, y)] = FenceHealth;

    }
    else if(Grid[x][y] == 2)//Castle
    {
        ObjectsGrid[x][y] = new ClanCastle(CastleHealth, pixMapDim, TroopDamage);
        castleIndX = x;
        castleIndY = y;
    }
    else if(Grid[x][y] == 3)
    {
            ObjectsGrid[x][y] = new Cannon(CannonHealth, pixMapDim, TroopDamage);
            CannonPos.setX(x*pixMapDim);
            CannonPos.setY(y*pixMapDim);
            canindx = x;
            canindy = y;
    }

}

void GameLevel::renderData()
{
    for(int i = 0; i < Grid.size(); i++)
    {
        for(int j = 0; j < Grid[i].size(); j++)
        {
            renderIndex(i,j);
            if(ObjectsGrid[i][j]!=nullptr)
            {
                ObjectsGrid[i][j]->setPos(i*pixMapDim, j*pixMapDim);
                scene->addItem(ObjectsGrid[i][j]);
            }
        }
    }
}

//Handling mouse events
void GameLevel::mouseMoveEvent(QMouseEvent* event)
{
    QPointF temp = mapToScene(event->pos());

    mousePos = temp.toPoint();
    qreal mousex = mousePos.x();
    qreal mousey = mousePos.y();
    qreal canx = CannonPos.x();
    qreal cany = CannonPos.y();
    ObjectsGrid[canindx][canindy]->setTransformOriginPoint(ObjectsGrid[canindx][canindy]->boundingRect().center());
    ObjectsGrid[canindx][canindy]->setRotation((qAtan2((mousey - cany),(mousex - canx)))*(180/3.14));
    if (pressed && (!played)) {
        QTimer* intervalTimer = new QTimer();
        QObject::connect(intervalTimer, &QTimer::timeout, [this]() {
            Bullet* b = new Bullet(pixMapDim, CannonPos, mousePos, &Troopss, BulletMovTime);
            scene->addItem(b);
        });

        intervalTimer->start(10);
        QTimer::singleShot(10000, [intervalTimer]() {
            intervalTimer->stop();
            delete intervalTimer;
        });
        played = true;
    }
}

void GameLevel::mousePressEvent(QMouseEvent *event)
{
    QPointF scenePoint = mapToScene(event->pos());
    mousePos = scenePoint;
    Bullet* b = new Bullet(pixMapDim, CannonPos, mousePos, &Troopss, BulletMovTime);
    scene->addItem(b);
}
void GameLevel::keyPressEvent(QKeyEvent* event)
{

    if((!pressed) &&  event->key() == Qt::Key_Space)
    {
        pressed = true;
    }
}

//spawning troops in random location outside the fence
void GameLevel::spawnTroops()
{
    int x = rand() % Grid.size();
    int y = rand() % Grid[x].size();
    //condifion for handling the generated indices inside the fence
    while (Grid[x][y] != 4)
    {
        x = rand() % Grid.size();
        y = rand() % Grid[x].size();
    }
    QVector<QPair<int, int>> path = dijkstra(Grid, qMakePair(x, y), qMakePair(castleIndX, castleIndY));
    Troops* temp = new Troops(castleIndX*pixMapDim, castleIndY*pixMapDim, scene, x*pixMapDim, y*pixMapDim, 100, pixMapDim, &path, &Troopss, &BulletDamage, &numOfTroopsDead);
    Troopss.push_back(temp);
}

//delay function
void GameLevel:: delay(int millisecondsToWait)
{
    QEventLoop loop;
    QTimer::singleShot(millisecondsToWait, &loop, SLOT(quit()));
    loop.exec();
}
GameLevel::~GameLevel() {
    for (int i = 0; i < ObjectsGrid.size(); i++) {
        for (int j = 0; j < ObjectsGrid[i].size(); j++) {
            delete ObjectsGrid[i][j];
        }
    }
    delete timer;

}

//dijkstra to find the shortests path, return vector of pairs
typedef std::pair<int, std::pair<int, int>> pii;

const int dx[8] = {-1, 0, 1, 0, -1, -1, 1, 1};
const int dy[8] = {0, 1, 0, -1, -1, 1, -1, 1};

QVector<QPair<int, int>> GameLevel:: dijkstra(QVector<QVector<int>> &grid, QPair<int,int> start, QPair<int,int> end) {
    int rows = grid.size();
    int cols = grid[0].size();
    QVector<QVector<int>> dist(rows, QVector<int>(cols, std::numeric_limits<int>::max()));
    QVector<QVector<bool>> visited(rows, QVector<bool>(cols, false));
    QVector<QVector<QPair<int, int>>> prev(rows, QVector<QPair<int, int>>(cols, {-1, -1}));

    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;

    dist[start.first][start.second] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        pii top = pq.top();
        pq.pop();

//        int d = top.first;
        std::pair<int, int> v = top.second;

        if (visited[v.first][v.second]) continue;
        visited[v.first][v.second] = true;

        for (int i = 0; i < 4; ++i) {
            int nx = v.first + dx[i];
            int ny = v.second + dy[i];
            if (nx < 0 || nx >= rows || ny < 0 || ny >= cols) continue;
            int h = std::sqrt((nx - end.first)*(nx - end.first) + (ny - end.second)*(ny - end.second));
            int weight = (grid[nx][ny] != 1 ) ?  10 + h : h + 10 * weights[qMakePair(nx, ny)];
            if (i >= 4) weight *= std::sqrt(2);

            if (dist[v.first][v.second] + weight < dist[nx][ny]) {
                dist[nx][ny] = dist[v.first][v.second] + weight;
                prev[nx][ny] = v;
                pq.push({dist[nx][ny], {nx, ny}});
            }
        }
    }

    QVector<QPair<int, int>> path;
    for (QPair<int, int> v = end; v != std::make_pair(-1, -1); v = prev[v.first][v.second]) {
        path.push_back(v);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

bool GameLevel::over()
{
    qDebug() << "DONE";
    return ObjectsGrid[castleIndX][castleIndY]->getHealth() <= 0;
}
