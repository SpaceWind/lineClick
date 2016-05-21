#include "shopform.h"
#include "ui_shopform.h"

ShopForm::ShopForm(Shop *shop, DamageEffect *dmg, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShopForm)
{
    ui->setupUi(this);
    this->shop = shop;
    this->dmg = dmg;
    updateStarsUI();
}

ShopForm::~ShopForm()
{
    delete ui;
}

void ShopForm::updateStarsUI()
{
    QPixmap fullStar(":/red_star.ico");
    for (int i=0; i < shop->levels["dmgincrease"]; i++)
        this->findChild<QLabel*>("dmg_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["crit"]; i++)
        this->findChild<QLabel*>("crit_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["onhit"]; i++)
        this->findChild<QLabel*>("onhit_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["splash"]; i++)
        this->findChild<QLabel*>("splash_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["maxhpdamage"]; i++)
        this->findChild<QLabel*>("maxhp_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["currenthpdamage"]; i++)
        this->findChild<QLabel*>("currenthp_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["executehpdamage"]; i++)
        this->findChild<QLabel*>("executehp_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["armpen"]; i++)
        this->findChild<QLabel*>("armpen_" + QString::number(i+1))->setPixmap(fullStar);
    for (int i=0; i < shop->levels["percentarmpen"]; i++)
        this->findChild<QLabel*>("percentarmpen_" + QString::number(i+1))->setPixmap(fullStar);
    ui->button_armpen->setText("Купить [" + QString::number(shop->prices["armpen"].at(shop->levels["armpen"])) + "]");
    ui->button_armpen->setEnabled(shop->prices["armpen"].at(shop->levels["armpen"]) <= shop->currentValue);

    ui->button_percentarmpen->setText("Купить [" + QString::number(shop->prices["percentarmpen"].at(shop->levels["percentarmpen"])) + "]");
    ui->button_percentarmpen->setEnabled(shop->prices["percentarmpen"].at(shop->levels["percentarmpen"]) <= shop->currentValue);

    ui->button_executehp->setText("Купить [" + QString::number(shop->prices["executehpdmg"].at(shop->levels["executehpdamage"])) + "]");
    ui->button_executehp->setEnabled(shop->prices["executehpdmg"].at(shop->levels["executehpdamage"]) <= shop->currentValue);

    ui->button_currenthp->setText("Купить [" + QString::number(shop->prices["currenthpdmg"].at(shop->levels["currenthpdamage"])) + "]");
    ui->button_currenthp->setEnabled(shop->prices["currenthpdmg"].at(shop->levels["currenthpdamage"]) <= shop->currentValue);

    ui->button_maxhp->setText("Купить [" + QString::number(shop->prices["maxhpdmg"].at(shop->levels["maxhpdamage"])) + "]");
    ui->button_maxhp->setEnabled(shop->prices["maxhpdmg"].at(shop->levels["maxhpdamage"]) <= shop->currentValue);

    ui->button_splash->setText("Купить [" + QString::number(shop->prices["splash"].at(shop->levels["splash"])) + "]");
    ui->button_splash->setEnabled(shop->prices["splash"].at(shop->levels["splash"]) <= shop->currentValue);

    ui->button_crit->setText("Купить [" + QString::number(shop->prices["crit"].at(shop->levels["crit"])) + "]");
    ui->button_crit->setEnabled(shop->prices["crit"].at(shop->levels["crit"]) <= shop->currentValue);

    ui->button_onhit->setText("Купить [" + QString::number(shop->prices["onhit"].at(shop->levels["onhit"])) + "]");
    ui->button_onhit->setEnabled(shop->prices["onhit"].at(shop->levels["onhit"]) <= shop->currentValue);

    ui->button_damage->setText("Купить [" + QString::number(shop->prices["dmgincrease"].at(shop->levels["dmgincrease"])) + "]");
    ui->button_damage->setEnabled(shop->prices["dmgincrease"].at(shop->levels["dmgincrease"]) <= shop->currentValue);
}

bool ShopForm::eventFilter(QObject *, QEvent *e)
{
    if (e->type() == QEvent::FocusIn)
    {
        updateStarsUI();
        return true;
    }
    return false;
}

void ShopForm::on_button_damage_clicked()
{
    shop->upgrade(dmg,"dmgincrease");
    updateStarsUI();
}

void ShopForm::on_button_onhit_clicked()
{
    shop->upgrade(dmg,"onhit");
    updateStarsUI();
}

void ShopForm::on_button_crit_clicked()
{
    shop->upgrade(dmg, "crit");
    updateStarsUI();
}

void ShopForm::on_button_splash_clicked()
{
    shop->upgrade(dmg, "splash");
    updateStarsUI();
}

void ShopForm::on_button_maxhp_clicked()
{
    shop->upgrade(dmg, "maxhpdamage");
    updateStarsUI();
}

void ShopForm::on_button_currenthp_clicked()
{
    shop->upgrade(dmg, "currenthpdamage");
    updateStarsUI();
    //jhgjhgjhgjglkjk
}

void ShopForm::on_button_executehp_clicked()
{
    shop->upgrade(dmg, "executehpdamage");
    updateStarsUI();
}

void ShopForm::on_button_armpen_clicked()
{
    shop->upgrade(dmg, "armpen");
    updateStarsUI();
}

void ShopForm::on_button_percentarmpen_clicked()
{
    shop->upgrade(dmg, "percentarmpen");
    updateStarsUI();
}
