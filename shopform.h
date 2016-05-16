#ifndef SHOPFORM_H
#define SHOPFORM_H

#include <QWidget>

namespace Ui {
class ShopForm;
}

class ShopForm : public QWidget
{
    Q_OBJECT

public:
    explicit ShopForm(QWidget *parent = 0);
    ~ShopForm();

private:
    Ui::ShopForm *ui;
};

#endif // SHOPFORM_H
