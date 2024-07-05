#include "Bullet.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "Enemy.h"
#include "Game.h"

extern Game * game;

Bullet::Bullet(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){

    setPixmap(QPixmap(":/images/bullet.png").scaled(10,50));

    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));


    timer->start(50);

    hitSound = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);

    hitSound->setAudioOutput(audioOutput);
    hitSound->setSource(QUrl(":/CHICKEN SCREAMING SOUND EFFECT.mp3"));
   // hitSound->setVolume(100);  // Set volume to maximum
    audioOutput->setVolume(100);  // Set volume to maximum

}

void Bullet::move(){

    QList<QGraphicsItem *> colliding_items = collidingItems();


    for (int i = 0, n = colliding_items.size(); i < n; ++i){
        if (typeid(*(colliding_items[i])) == typeid(Enemy)){

            game->score->increase();

            if (hitSound->playbackState() == QMediaPlayer::PlayingState) {
                hitSound->setPosition(0); // Restart the sound if it's already playing
            }
            else if (hitSound->playbackState() == QMediaPlayer::StoppedState) {
                hitSound->play();
            }

            qDebug() << "Hit sound playback state:" << hitSound->playbackState();



            scene()->removeItem(colliding_items[i]);
            scene()->removeItem(this);


            delete colliding_items[i];
            delete this;


            return;
        }
    }


    setPos(x(),y()-10);

    if (pos().y() < 0){
        scene()->removeItem(this);
        delete this;
    }
}
