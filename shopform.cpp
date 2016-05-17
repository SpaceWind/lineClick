#include "shopform.h"
#include "ui_shopform.h"

ShopForm::ShopForm(Shop *shop, DamageEffect *dmg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopForm)
{
    ui->setupUi(this);
    this->shop = shop;
    this->dmg = dmg;

}

ShopForm::~ShopForm()
{
    delete ui;
}

void ShopForm::updateStarsUI()
{
    QPixmap fullStar(":/red_star.ico");
    for (int i=0; i < levels["dmgincrease"]; i++)
        this->findChild<QLabel*>("dmg_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["crit"]; i++)
        this->findChild<QLabel*>("crit_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["onhit"]; i++)
        this->findChild<QLabel*>("onhit_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["splash"]; i++)
        this->findChild<QLabel*>("splash_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["maxhpdamage"]; i++)
        this->findChild<QLabel*>("maxhp_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["currenthpdamage"]; i++)
        this->findChild<QLabel*>("currenthp_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["executehpdamage"]; i++)
        this->findChild<QLabel*>("execute_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["armpen"]; i++)
        this->findChild<QLabel*>("armpen_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < levels["percentarmpen"]; i++)
        this->findChild<QLabel*>("percentarmpen_" + QString::number(i+1))->setPixmap(fullStar);
    ui->button_armpen->setText("Купить [" + QString::number(shop->prices["armpen"].at(levels["armpen"])) + "]");
    ui->button_percentarmpen->setText("Купить [" + QString::number(shop->prices["percentarmpen"].at(levels["percentarmpen"])) + "]");
    ui->button_executehp->setText("Купить [" + QString::number(shop->prices["executehpdamage"].at(levels["executehpdamage"])) + "]");
    ui->button_currenthp->setText("Купить [" + QString::number(shop->prices["currenthpdamage"].at(levels["currenthpdamage"])) + "]");
    ui->button_maxhp->setText("Купить [" + QString::number(shop->prices["maxhpdamage"].at(levels["maxhpdamage"])) + "]");
    ui->button_splash->setText("Купить [" + QString::number(shop->prices["splash"].at(levels["splash"])) + "]");
    ui->button_crit->setText("Купить [" + QString::number(shop->prices["crit"].at(levels["crit"])) + "]");
    ui->button_onhit->setText("Купить [" + QString::number(shop->prices["onhit"].at(levels["onhit"])) + "]");
    ui->button_damage->setText("Купить [" + QString::number(shop->prices["dmgincrease"].at(levels["dmgincrease"])) + "]");

}
