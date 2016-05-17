#ifndef LINEDESCRIPTOR_H
#define LINEDESCRIPTOR_H

#include <QObject>
#include <QHash>
#include <QList>

struct DamageEffect
{
    DamageEffect();
    ~DamageEffect(){;}
    int getDamage(int hp, int maxhp, int speed, int armor);
    int value;
    int onhitChance,onhitDamage;
    double critMod; int critChance;
    int splash;
    double maxHPDamage, currentHPDamage, executeHPDamage;
    int armpen, percentArmpen;
    int dmgIncreasePercent;
};

struct Shop
{
    QHash<QString,QList<double> > prices;
    QHash<QString,QList<double> > items;
    QHash<QString,int> levels;
    double currentValue;

    void upgrade(DamageEffect* dmg, QString effect);
};

struct LineDescriptor
{
public:
    LineDescriptor();

    int hp, maxhp;
    int speed;
    int armor;
    bool isActive;
};

#endif // LINEDESCRIPTOR_H
