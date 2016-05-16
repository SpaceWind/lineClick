#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QEvent>
#include <QList>
#include <QProgressBar>
#include <QTimer>
#include <QResizeEvent>
#include "linedescriptor.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void initLines();
    QProgressBar * getPBByIndex(int i);
    QList<double> configToArray(QJsonObject root, QString name);

    void keyPress(QKeyEvent * key);
public slots:
    bool eventFilter(QObject *, QEvent * event);
    void gameTimerTick();
    void nextLevelTick();
    void scoresTimerTick();
    void resizeEvent(QResizeEvent * event);

private slots:
    void on_pushButton_clicked();

    void on_label_3_linkActivated(const QString &link);

private:
    Ui::MainWindow *ui;
    int currentPos;
    DamageEffect dmg;
    QList<LineDescriptor> lines;
    Shop shop;
    QTimer * gameTimer;
    QTimer * nextLevelTimer;
    QTimer * scoresTimer;
    double currentLevel;
};

#endif // MAINWINDOW_H
