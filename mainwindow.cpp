#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <math.h>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonValue>
#include <QFile>
#include <QGestureEvent>
#include <QGesture>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    grabGesture(Qt::SwipeGesture);
    grabGesture(Qt::PanGesture);

    setAttribute(Qt::WA_AcceptTouchEvents);

    ui->setupUi(this);
    ui->pushButton->installEventFilter(this);
    for (int i = 0; i<7; ++i)
        getPBByIndex(i)->installEventFilter(this);
    initLines();
    currentPos = 0;
    shop.currentValue = 0;
    gameTimer = new QTimer();
    gameTimer->setInterval(100);
    nextLevelTimer = new QTimer();
    nextLevelTimer->setInterval(60000);
    scoresTimer = new QTimer();
    scoresTimer->setInterval(200);

    connect(nextLevelTimer,SIGNAL(timeout()),this,SLOT(nextLevelTick()));
    connect(scoresTimer,SIGNAL(timeout()),this,SLOT(scoresTimerTick()));
    connect(gameTimer,SIGNAL(timeout()),this, SLOT(gameTimerTick()));
    gameTimer->start();
    scoresTimer->start();
    nextLevelTimer->start();
    this->grabGesture(Qt::SwipeGesture);
    QList<QWidget*> c = this->findChildren<QWidget*>();
    for (int i = 0; i< c.count(); i++)
    {
        c[i]->installEventFilter(this);
        c[i]->setAttribute(Qt::WA_AcceptTouchEvents);
        c[i]->grabGesture(Qt::SwipeGesture);
        c[i]->grabGesture(Qt::PanGesture);
    }
    currentLevel = 1.0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initLines()
{
    QFile balanceFile(":/balance.txt");
    balanceFile.open(QFile::ReadOnly);
    QJsonDocument doc = QJsonDocument::fromJson(balanceFile.readAll());
    QJsonObject root = doc.object();
    QJsonObject pricesObject = root["prices"].toObject();
    QJsonArray linesArray = root["lines"].toArray();
    int index = 0;
    foreach (const QJsonValue &v, linesArray)
    {
        QJsonObject lineObject = v.toObject();
        LineDescriptor line;
        line.armor = lineObject["armor"].toInt();
        line.hp = lineObject["hp"].toInt();
        line.maxhp = lineObject["maxhp"].toInt();
        line.speed = lineObject["speed"].toInt();

        getPBByIndex(index)->setMaximum(line.maxhp);
        getPBByIndex(index)->setValue(line.hp);
        lines.append(line);
        index++;
    }
    dmg.value = root["basedmg"].toInt();
    shop.items["dmgincrease"] = configToArray(root,"dmgincrease");
    shop.items["critchance"] = configToArray(root,"critchance");
    shop.items["critmult"] = configToArray(root,"critmult");
    shop.items["onhitchance"] = configToArray(root, "onhitchance");
    shop.items["onhitdamage"] = configToArray(root,"onhitdamage");
    shop.items["splash"] = configToArray(root,"splash");
    shop.items["maxhpdmg"] = configToArray(root,"maxhpdmg");
    shop.items["currenthpdmg"] = configToArray(root,"currenthpdmg");
    shop.items["executehpdmg"] = configToArray(root,"executehpdmg");
    shop.items["armpen"] = configToArray(root,"armpen");
    shop.items["percentarmpen"] = configToArray(root,"percentarmpen");

    shop.prices["dmgincrease"] = configToArray(pricesObject,"dmgincrease");
    shop.prices["crit"] = configToArray(pricesObject,"crit");
    shop.prices["onhit"] = configToArray(pricesObject, "onhit");
    shop.prices["splash"] = configToArray(pricesObject,"splash");
    shop.prices["maxhpdmg"] = configToArray(pricesObject,"maxhpdmg");
    shop.prices["currenthpdmg"] = configToArray(pricesObject,"currenthpdmg");
    shop.prices["executehpdmg"] = configToArray(pricesObject,"executehpdmg");
    shop.prices["armpen"] = configToArray(pricesObject,"armpen");
    shop.prices["percentarmpen"] = configToArray(pricesObject,"percentarmpen");
    shop.upgrade(dmg,"init");
    balanceFile.close();
}

QProgressBar *MainWindow::getPBByIndex(int i)
{
    switch (i)
    {
    case 0:
        return ui->progressBar;
    case 1:
        return ui->progressBar_2;
    case 2:
        return ui->progressBar_3;
    case 3:
        return ui->progressBar_4;
    case 4:
        return ui->progressBar_5;
    case 5:
        return ui->progressBar_6;
    case 6:
        return ui->progressBar_7;
    }
    return 0;
}

QList<double> MainWindow::configToArray(QJsonObject root, QString name)
{
    QList<double> result;
    QJsonArray data = root[name].toArray();
    foreach (const QJsonValue &v, data)
        result.append(v.toDouble());
    return result;
}

bool MainWindow::eventFilter(QObject *, QEvent *event)
{
    if(event->type() == QEvent::KeyPress)
    {
        keyPress(static_cast<QKeyEvent*>(event));
    }
    if (event->type() == QEvent::Gesture)
    {
        QGestureEvent * gEvent = static_cast<QGestureEvent*>(event);
        if (QGesture *swipe = gEvent->gesture(Qt::SwipeGesture))
        {
            QSwipeGesture * swipeGesture = static_cast<QSwipeGesture *>(swipe);
            if (swipeGesture->horizontalDirection() == QSwipeGesture::Left)
            {
                currentPos -=1;
                if (currentPos < 0)
                    currentPos = 6;
                ui->pushButton->move(getPBByIndex(currentPos)->geometry().left()-ui->groupBox->geometry().left(), ui->pushButton->geometry().top());
            }
            else if (swipeGesture->horizontalDirection() == QSwipeGesture::Right)
            {
                currentPos +=1;
                if (currentPos > 6)
                    currentPos = 0;
                ui->pushButton->move(getPBByIndex(currentPos)->geometry().left()-ui->groupBox->geometry().left(), ui->pushButton->geometry().top());
            }
        }
    }
    return false;
}

void MainWindow::keyPress(QKeyEvent *key)
{
    if (key->key() == Qt::Key_Left)
    {
        currentPos -=1;
        if (currentPos < 0)
            currentPos = 6;
        ui->pushButton->move(getPBByIndex(currentPos)->geometry().left()-ui->groupBox->geometry().left(), ui->pushButton->geometry().top());
    }
    else if (key->key() == Qt::Key_Right)
    {
        currentPos +=1;
        if (currentPos > 6)
            currentPos = 0;
        ui->pushButton->move(getPBByIndex(currentPos)->geometry().left()-ui->groupBox->geometry().left(), ui->pushButton->geometry().top());
    }
    else if (key->key() == Qt::Key_P)
    {
        qDebug() <<"pause pressed" << key->type();
        if (gameTimer->isActive())
            gameTimer->stop();
        else
            gameTimer->start();
    }
}

void MainWindow::gameTimerTick()
{
    int lineNumber = std::rand()%7;
    while (lines[lineNumber].isActive == false)
        lineNumber = std::rand()%7;

    lines[lineNumber].hp += lines.at(lineNumber).speed;
    getPBByIndex(lineNumber)->setValue(lines.at(lineNumber).hp);
    int index = 0;
    foreach (const LineDescriptor &l, lines)
    {
        if (l.hp > l.maxhp && l.isActive)
        {
            getPBByIndex(index)->setStyleSheet("QProgressBar{border: 1px solid grey;border-radius: 6px;background-color: #DDDDDD;}QProgressBar::chunk {background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(160, 120, 170, 255), stop:1 rgba(170, 138, 180, 255));border-radius: 6px;}");
            lines[index].isActive = false;
        }
        index++;
    }
}

void MainWindow::nextLevelTick()
{
    for (int i =0; i< lines.count(); i++)
    {
        lines[i].armor = lines[i].armor * 110/100;
        lines[i].speed = lines[i].speed * 110/100;
        lines[i].maxhp = lines[i].maxhp * 110/100;
        getPBByIndex(i)->setMaximum(lines[i].maxhp);
    }
    currentLevel += 1.0;
    this->setWindowTitle("LineClicker! Level " + QString::number(currentLevel));
}

void MainWindow::scoresTimerTick()
{
    int totalHp=0, currentHp = 0;
    foreach (const LineDescriptor &l, lines)
    {
        totalHp+=l.maxhp;
        if (l.isActive)
            currentHp+=l.hp;
    }
    double ffCoef = double(currentHp)/double(totalHp);
    ffCoef *= pow(1.1,currentLevel);
    shop.currentValue += ffCoef * 0.666;
    ui->label_2->setText("Очки: " + QString::number(int(shop.currentValue)));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //ui->pushButton->setMinimumWidth(ui->progressBar->width()*75/100);
    //ui->pushButton->setMinimumHeight(ui->progressBar->width()*50/100);
}

void MainWindow::on_pushButton_clicked()
{
    if (lines[currentPos].isActive == false || gameTimer->isActive() == false)
        return;
    int damage = dmg.getDamage(lines[currentPos].hp,lines[currentPos].maxhp,lines[currentPos].speed,lines[currentPos].armor);
    QList<int> linesNeedToUpdate;
    linesNeedToUpdate.append(currentPos);
    if (dmg.splash > 0)
    {
        int leftPos = currentPos-1;
        int rightPos = currentPos+1;
        if (leftPos >0)
        {
            lines[leftPos].hp -= damage * dmg.splash / 100;
            linesNeedToUpdate.append(leftPos);
        }
        if (rightPos < 7)
        {
            lines[rightPos].hp -= damage * dmg.splash / 100;
            linesNeedToUpdate.append(rightPos);
        }
    }
    lines[currentPos].hp -= damage;
    if (lines[currentPos].hp > 0)
        shop.currentValue += double(damage)*0.015;
    foreach (const int &l, linesNeedToUpdate)
        getPBByIndex(l)->setValue(lines[l].hp);
    ui->label->setText("DMG: " + QString::number(damage) + " hp=" + QString::number(lines[currentPos].hp));
}

void MainWindow::on_label_3_linkActivated(const QString &link)
{
    qDebug() << "link:" << link;
}
