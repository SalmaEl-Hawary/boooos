#include "Enemy.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include "Game.h"

extern Game * game;

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    int random_number = rand() % 700;
    setPos(random_number,0);


    setPixmap(QPixmap(":/images/Militarychicken.png").scaled(100,100));



    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));


    timer->start(50);
}

void Enemy::move() {
    setPos(x(), y() + 5);

    if (pos().y() > 600) {
        scene()->removeItem(this);
        delete this;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
        if (typeid(*(colliding_items[i])) == typeid(Player) && game->health->getHealth() > 0) {
            game->health->decrease();
            scene()->removeItem(this);
            delete this;
            return;
        }
    }

    if (game->health->getHealth() <= 0) {
        game->scene->clear();

        QGraphicsTextItem *gameOverText = new QGraphicsTextItem("Game Over");
        QFont gameOverFont("times", 30);
        gameOverText->setFont(gameOverFont);
        gameOverText->setDefaultTextColor(Qt::red);
        gameOverText->setPos(300, 250);
        game->scene->addItem(gameOverText);

    }
}

