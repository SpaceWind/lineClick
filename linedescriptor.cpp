#include "linedescriptor.h"

LineDescriptor::LineDescriptor()
{
    isActive = true;
}



DamageEffect::DamageEffect()
{
    value = onhitChance = onhitDamage = critChance =
            critMod = splash = maxHPDamage = currentHPDamage =
            executeHPDamage = armpen = percentArmpen =
            dmgIncreasePercent = 0;
}

int DamageEffect::getDamage(int hp, int maxhp, int speed, int armor)
{
    int result = value;
    if (dmgIncreasePercent > 0)
        result = result * (dmgIncreasePercent + 100) / 100;
    if (onhitChance != 0 && onhitDamage !=0)
    {
        int randomValue = std::rand()%100;
        if (randomValue <= onhitChance)
            result += onhitDamage;
    }
    if (critChance != 0 && critMod != 0.0)
    {
        int randomValue = std::rand()%100;
        if (randomValue < critChance)
            result *= critMod;

    }
    if (maxHPDamage != 0.0)
    {
        result += maxhp*maxHPDamage*0.01;
    }
     if (currentHPDamage != 0.0)
    {
        result += hp*currentHPDamage*0.01;
    }
    if (executeHPDamage != 0.0)
    {
        result += (maxhp-hp)*executeHPDamage*0.01;
    }
    if (percentArmpen != 0)
    {
        armor = armor * (100-percentArmpen)/100;
    }
    if (armpen != 0)
    {
        armor -= armpen;
        if (armor < 0)
            armor = 0;
    }
    double armorPercent = 1. - double(armor)/double(armor+100);
    return result * armorPercent;
}
void Shop::upgrade(DamageEffect *dmg, QString effect)
{
    if (effect == "init")
    {
        levels["armpen"] = 0;
        levels["crit"] = 0;
        levels["currenthpdamage"] = 0;
        levels["executehpdamage"] = 0;
        levels["maxhpdamage"] = 0;
        levels["onhit"] = 0;
        levels["percentarmpen"] = 0;
        levels["splash"] = 0;
        levels["dmgincrease"] = 0;
    }
    if (effect == "armpen" && levels["armpen"] < 8)
    {
        dmg->armpen += items["armpen"].at(levels["armpen"]);
        currentValue -= prices["armpen"].at(levels["armpen"]);
        levels["armpen"] += 1;
    }
    if (effect == "crit" && levels["crit"] < 8)
    {
        dmg->critChance += items["critchance"].at(levels["crit"]);
        dmg->critMod += items["critmult"].at(levels["crit"]);
        currentValue -= prices["crit"].at(levels["crit"]);
        levels["crit"] += 1;
    }
    if (effect == "currenthpdamage" && levels["currenthpdamage"] < 8)
    {
        dmg->currentHPDamage += items["currenthpdmg"].at(levels["currenthpdamage"]);
        currentValue -= prices["currenthpdmg"].at(levels["currenhpdamage"]);
        levels["currenthpdamage"] += 1;
    }
    if (effect == "maxhpdamage" && levels["maxhpdamage"] < 8)
    {
        dmg->maxHPDamage += items["maxhpdmg"].at(levels["maxhpdamage"]);
        currentValue -= prices["maxhpdmg"].at(levels["maxhpdamage"]);
        levels["maxhpdamage"] += 1;
    }
    if (effect == "executehpdamage" && levels["executehpdamage"] < 8)
    {
        dmg->executeHPDamage += items["executehpdmg"].at(levels["executehpdamage"]);
        currentValue -= prices["executehpdmg"].at(levels["executehpdamage"]);
        levels["executehpdamage"] += 1;

    }
    if (effect == "onhit" && levels["onhit"] < 8)
    {
        dmg->onhitChance += items["onhitchance"].at(levels["onhit"]);
        dmg->onhitDamage += items["onhitdamage"].at(levels["onhit"]);
        currentValue -= prices["onhit"].at(levels["onhitdamage"]);
        levels["onhit"] += 1;
    }
    if (effect == "percentarmpen" && levels["percentarmpen"] < 8)
    {
        dmg->percentArmpen += items["percentarmpen"].at(levels["percentarmpen"]);
        currentValue -= prices["percentarmpen"].at(levels["percentarmpen"]);
        levels["percentarmpen"] += 1;
    }
    if (effect == "splash" && levels["splash"] < 8)
    {
        dmg->splash += items["splash"].at(levels["splash"]);
        currentValue -= prices["splash"].at(levels["splash"]);
        levels["splash"] += 1;
    }
    if (effect == "dmgincrease" && levels["dmgincrease"] < 8)
    {
        dmg->value += items["dmgincrease"].at(levels["dmgincrease"]);
        currentValue -= prices["dmgincrease"].at(levels["dmgincrease"]);
        levels["dmgincrease"] += 1;
    }
}
