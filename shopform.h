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

private:
    Ui::ShopForm *ui;
    Shop* shop;
    DamageEffect * dmg;
};

#endif // SHOPFORM_H
