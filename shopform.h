#ifndef SHOPFORM_H
#define SHOPFORM_H

#include <QWidget>
#include "linedescriptor.h"

namespace Ui {
class ShopForm;
}

class ShopForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShopForm(Shop* shop, DamageEffect* dmg, QWidget *parent = 0);
    ~ShopForm();
    void updateStarsUI();

private slots:
    bool eventFilter(QObject *, QEvent *e);
    void on_button_damage_clicked();

    void on_button_onhit_clicked();

    void on_button_crit_clicked();

    void on_button_splash_clicked();

    void on_button_maxhp_clicked();

    void on_button_currenthp_clicked();

    void on_button_executehp_clicked();

    void on_button_armpen_clicked();

    void on_button_percentarmpen_clicked();

private:
    Ui::ShopForm *ui;
    Shop* shop;
    DamageEffect * dmg;
};

#endif // SHOPFORM_H
