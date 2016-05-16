#include "shopform.h"
#include "ui_shopform.h"

ShopForm::ShopForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopForm)
{
    ui->setupUi(this);
}

ShopForm::~ShopForm()
{
    delete ui;
}
