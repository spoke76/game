#include "spider.h"
#include "math.h"

static const double Pi = 3.14;
static double TwoPi = 2.0 * Pi;

static qreal normalizeAngle(qreal angle)
{
    while (angle < 0)
        angle += TwoPi;
    while (angle > TwoPi)
        angle -= TwoPi;
    return angle;
}

Spider::Spider(QGraphicsItem *target, QObject *parent) :
    QObject(parent), QGraphicsItem()
{
    angle = 0;      // Задаём угол поворота графического объекта
    steps = 0;      // Задаём стартовое положение ножек мухи
    countForSteps = 0;      // Счётчик для отсчета тиков таймера, при которых мы нажимали на кнопки
    setRotation(angle);     // Устанавливаем угол поворота графического объекта

    this->target = target;  // Устанавливаем цель паука

    timer = new QTimer();   // Инициализируем игровой таймер паука
    // подключаем сигнал таймера к игровому слоту паука
    connect(timer, &QTimer::timeout, this, &Spider::slotGameTimer);
    timer->start(15);       // Запускаем таймер
}

Spider::~Spider()
{

}

QRectF Spider::boundingRect() const
{
    return QRectF(-40,-50,80,100);
}

void Spider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Рисуем ножки, без ножек паук не догонит муху
    painter->setPen(QPen(Qt::black, 2));
    if(steps == 0){     // Первое положение ножек
        // Left 1
        painter->drawLine(-24,-45,-28,-35);
        painter->drawLine(-28,-35,-22,-10);
        painter->drawLine(-22,-10,0,0);
        // Right 1
        painter->drawLine(24,-45,28,-35);
        painter->drawLine(28,-35,22,-10);
        painter->drawLine(22,-10,0,0);

        // Left 2
        painter->drawLine(-35,-38,-30,-18);
        painter->drawLine(-30,-18,-25,-3);
        painter->drawLine(-25,-3,0,0);
        // Right 2
        painter->drawLine(35,-38,30,-18);
        painter->drawLine(30,-18,25,-3);
        painter->drawLine(25,-3,0,0);

        // Left 3
        painter->drawLine(-35,38,-30,18);
        painter->drawLine(-30,18,-25,3);
        painter->drawLine(-25,3,0,0);
        // Right 3
        painter->drawLine(35,38,30,18);
        painter->drawLine(30,18,25,3);
        painter->drawLine(25,3,0,0);

        // Left 4
        painter->drawLine(-24,45,-28,35);
        painter->drawLine(-28,35,-22,10);
        painter->drawLine(-22,10,0,0);
        // Right 4
        painter->drawLine(24,45,28,35);
        painter->drawLine(28,35,22,10);
        painter->drawLine(22,10,0,0);
    } else if (steps == 1){     // Второе положение ножек
        // Left 1
        painter->drawLine(-23,-40,-24,-30);
        painter->drawLine(-24,-30,-19,-9);
        painter->drawLine(-19,-9,0,0);
        // Right 1
        painter->drawLine(20,-50,23,-40);
        painter->drawLine(23,-40,15,-12);
        painter->drawLine(15,-12,0,0);

        // Left 2
        painter->drawLine(-30,-35,-27,-24);
        painter->drawLine(-27,-24,-23,-5);
        painter->drawLine(-23,-5,0,0);
        // Right 2
        painter->drawLine(40,-27,35,-10);
        painter->drawLine(35,-10,28,-1);
        painter->drawLine(28,-1,0,0);

        // Left 3
        painter->drawLine(-40,27,-35,10);
        painter->drawLine(-35,10,-28,1);
        painter->drawLine(-28,1,0,0);
        // Right 3
        painter->drawLine(30,35,27,24);
        painter->drawLine(27,24,23,5);
        painter->drawLine(23,5,0,0);

        // Left 4
        painter->drawLine(-20,50,-27,30);
        painter->drawLine(-27,30,-20,12);
        painter->drawLine(-20,12,0,0);
        // Right 4
        painter->drawLine(23,40,24,30);
        painter->drawLine(24,30,19,9);
        painter->drawLine(19,9,0,0);
    } else if (steps == 2){     // Третье положение ножек
        // Left 1
        painter->drawLine(-20,-50,-23,-40);
        painter->drawLine(-23,-40,-15,-12);
        painter->drawLine(-15,-12,0,0);
        // Right 1
        painter->drawLine(23,-40,24,-30);
        painter->drawLine(24,-30,19,-9);
        painter->drawLine(19,-9,0,0);

        // Left 2
        painter->drawLine(-40,-27,-35,-10);
        painter->drawLine(-35,-10,-28,-1);
        painter->drawLine(-28,-1,0,0);
        // Right 2
        painter->drawLine(30,-35,27,-24);
        painter->drawLine(27,-24,23,-5);
        painter->drawLine(23,-5,0,0);

        // Left 3
        painter->drawLine(-30,35,-27,24);
        painter->drawLine(-27,24,-23,5);
        painter->drawLine(-23,5,0,0);
        // Right 3
        painter->drawLine(40,27,35,10);
        painter->drawLine(35,10,28,1);
        painter->drawLine(28,1,0,0);

        // Left 4
        painter->drawLine(-23,40,-24,30);
        painter->drawLine(-24,30,-19,9);
        painter->drawLine(-19,9,0,0);
        // Right 4
        painter->drawLine(20,50,27,30);
        painter->drawLine(27,30,20,12);
        painter->drawLine(20,12,0,0);
    }

    painter->setPen(QPen(Qt::black, 1));
    // Левое Жвало
    QPainterPath path1(QPointF(0, -20));
    path1.cubicTo(0, -20, -5, -25, -3, -35);
    path1.cubicTo(-3,-35,-15,-25,-8,-17);
    path1.cubicTo(-8,-17,-5,15,0,-20 );
    painter->setBrush(Qt::black);
    painter->drawPath(path1);

    // Правое Жвало
    QPainterPath path2(QPointF(0, -20));
    path2.cubicTo(0, -20, 5, -25, 3, -35);
    path2.cubicTo(3,-35,15,-25,8,-17);
    path2.cubicTo(8,-17,5,15,0,-20 );
    painter->setBrush(Qt::black);
    painter->drawPath(path2);

    // Голова
    painter->setBrush(QColor(146, 115, 40, 255));
    painter->drawEllipse(-10,-25,20,15);
    // Тушка
    painter->drawEllipse(-15, -15, 30, 30);
    // Жопка
    painter->drawEllipse(-20, 0, 40,50);
    painter->setPen(QPen(Qt::white,3));
    painter->drawLine(-10,25,10,25);
    painter->drawLine(0,35,0,15);
    // Левое глазище
    painter->setPen(QPen(Qt::black,1));
    painter->setBrush(Qt::red);
    painter->drawEllipse(-8,-23,6,8);
    // Правое глазище
    painter->setBrush(Qt::red);
    painter->drawEllipse(2,-23,6,8);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Spider::slotGameTimer()
{
    // Определяем расстояние до Мухи
    QLineF lineToTarget(QPointF(0, 0), mapFromItem(target, 0, 0));
    // Угол поворота в направлении к Мухе
    qreal angleToTarget = ::acos(lineToTarget.dx() / lineToTarget.length());
    if (lineToTarget.dy() < 0)
        angleToTarget = TwoPi - angleToTarget;
    angleToTarget = normalizeAngle((Pi - angleToTarget) + Pi / 2);

    /* В Зависимости от того, слева или справа находится Муха от Паука,
     * устанавливаем направление поворота паука в данном тике таймера
     * Скорость разворота зависит от угла, на который необходимо повернуться пауку
     * */
    if (angleToTarget > 0 && angleToTarget < Pi) {
        // Rotate left
        if(angleToTarget > Pi / 10){
            angle = -15;
        } else if(angleToTarget > Pi / 20){
            angle = -5;
        } else {
            angle = -1;
        }
    } else if (angleToTarget <= TwoPi && angleToTarget > (TwoPi - Pi)) {
        // Rotate right
        if(angleToTarget < (TwoPi - Pi / 10)){
            angle = 15;
        } else if(angleToTarget < (TwoPi - Pi / 20)){
            angle = 5;
        } else {
            angle = 1;
        }
    } else if(angleToTarget == 0) {
        angle = 0;
    }

    setRotation(rotation() + angle); // Разворачиваемся

    // Бежим в сторону мухи
    if(lineToTarget.length() >= 40){
        setPos(mapToParent(0, -(qrand() % ((4 + 1) - 1) + 1)));

        // Двигаем ножками, Dance, dance, Spidy !!!
        countForSteps++;
        if(countForSteps == 6){
            steps = 1;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 12){
            steps = 0;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 18){
            steps = 2;
            update(QRectF(-40,-50,80,100));
        } else if (countForSteps == 24) {
            steps = 0;
            update(QRectF(-40,-50,80,100));
            countForSteps = 0;
        }
    }

    /* Производим проверку на то, наткнулся ли паук на какой-нибудь
     * элемент на графической сцене.
     * Для этого определяем небольшую область перед пауком,
     * в которой будем искать элементы
     * */
    QList<QGraphicsItem *> foundItems = scene()->items(QPolygonF()
                                                           << mapToScene(0, 0)
                                                           << mapToScene(-2, -2)
                                                           << mapToScene(2, -2));
    /* После чего проверяем все элементы.
     * Один из них будет сам Паук - с ним ничего не делаем.
     * А с остальными высылаем сигнал в ядро игры
     * */
    foreach (QGraphicsItem *item, foundItems) {
        if (item == this)
            continue;
        if(item == target){
            emit signalCheckGameOver();
        }
    }

    /* Проверка выхода за границы поля
     * Если объект выходит за заданные границы, то возвращаем его назад
     * */
    if(this->x() - 10 < -250){
        this->setX(-240);       // слева
    }
    if(this->x() + 10 > 250){
        this->setX(240);        // справа
    }

    if(this->y() - 10 < -250){
        this->setY(-240);       // сверху
    }
    if(this->y() + 10 > 250){
        this->setY(240);        // снизу
    }
}

/* Функция паузы, отвечает за включение и отключение паузы
 * */
void Spider::pause()
{
    if(timer->isActive()){
        timer->stop();
    } else {
        timer->start(15);
    }
}
