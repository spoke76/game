#ifndef SPIDER_H
#define SPIDER_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QPainter>
#include <QTimer>
#include <QDebug>

class Spider : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Spider(QGraphicsItem * target, QObject *parent = 0);
    ~Spider();
    void pause();   // Сигнал для инициализации паузы

signals:
    void signalCheckGameOver();  // Сигнал на вызов состояния Game Over

public slots:

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    qreal angle;        // Угол поворота графического объекта
    int steps;          // Номер положения ножек паука
    int countForSteps;  // Счетчик для изменения полоэения ножек
    QTimer      *timer;     // Внутренний таймер паука, по которому инициализируется его движение
    QGraphicsItem * target; // Цель паука, данный объект приравнивается объекту Мухи

private slots:
    void slotGameTimer();   // Слот игрового таймера паука
};

#endif // SPIDER_H
