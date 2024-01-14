#include <QApplication>
#include <QGraphicsScene>
#include "gamelevel.h"
#include <QDebug>
#include <QEventLoop>
#include <QTimer>
#include <vector>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QKeyEvent>
#include "transition.h"
//#include "startwidget.h"
#include "winwidget.h"
//delay function
void delay(int millisecondsToWait)
{
    QEventLoop loop;
    QTimer::singleShot(millisecondsToWait, &loop, SLOT(quit()));
    loop.exec();
}
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Create the game levels and add them to the vector
    // Each level has different parameters for the game configuration
    transition* tan = new transition();
    std::vector<GameLevel*> levels;
    GameLevel* level1 = new GameLevel(nullptr, 100, 50, 10000, 10000, 500, 2000, INT_MAX, 20, 50, 300);
    levels.push_back(level1);
//    level1->deleteLater();
    GameLevel* level2 = new GameLevel(nullptr, 200, 50, 8000, 10000, 500, 2500, INT_MAX, 100, 100, 300);
    levels.push_back(level2);
    GameLevel* level3 = new GameLevel(nullptr, 200, 100, 4000, 10000, 700, 3000, INT_MAX, 100, 100, 200);
    levels.push_back(level3);
    GameLevel* level4 = new GameLevel(nullptr, 200, 100, 2000, 10000, 700, 3500, INT_MAX, 100, 100, 150);
    levels.push_back(level4);
    GameLevel* level5 = new GameLevel(nullptr, 200, 100, 500, 10000, 800, 4000, INT_MAX, 100, 100, 150);
    levels.push_back(level5);
//    Startwidget* starting = new Startwidget();
//    starting->show();

    //switching between levels using loop and timers
//    for (GameLevel* level : levels) {
//        delay(10);
//        level->show();
//        level->start();

//        QTimer::singleShot(1000*60, &app, &QApplication::quit);
//        int result = app.exec();
//        if (level->over() || result != 0) {
//            delete tan;
//            return 0;
//        }
//        level->close();
//        tan->show();
//        delay(1000);
//        tan->hide();
//    }
    for(size_t i = 0; i < levels.size(); i++)
    {
        delay(10);
        levels[i]->show();
        levels[i]->start();

        QTimer::singleShot(1000*60, &app, &QApplication::quit);
        int result = app.exec();
        if (levels[i]->over() || result != 0) {
            delete tan;
            return 0;
        }
        levels[i]->close();
        tan->show();
        delay(1000);
        tan->hide();
        GameLevel* temp = levels[i];
        levels.erase(levels.begin() + i);
        delete temp;
    }
    delete tan;
    //after the 5 levels, show win window
    winwidget win;
    win.show();
    delay(1000);
    win.hide();
    return 0;
}
