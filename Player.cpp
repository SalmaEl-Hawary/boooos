#include "Player.h"
#include <QGraphicsScene>
#include <QKeyEvent>
#include "Bullet.h"
#include "Enemy.h"

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){

    bulletsound = new QMediaPlayer();
    bulletsound->setSource(QUrl(":/Gunshot Sound Effect.mp3"));


    setPixmap(QPixmap(":/images/spaceship.png").scaled(100,100));
}

void Player::keyPressEvent(QKeyEvent *event){

    if (event->key() == Qt::Key_Left){
        if (pos().x() > 0)
            setPos(x()-10,y());
    }
    else if (event->key() == Qt::Key_Right){
        if (pos().x() + 100 < 800)
            setPos(x()+10,y());
    }

    else if (event->key() == Qt::Key_Space){

        Bullet * bullet = new Bullet();
        bullet->setPos(x()+45,y());
        scene()->addItem(bullet);


       /* if (bulletsound.stat() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if (bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }*/

    }
}

void Player::spawn(){

    Enemy * enemy = new Enemy();
    scene()->addItem(enemy);
}
