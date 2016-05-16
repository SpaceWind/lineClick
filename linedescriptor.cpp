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
        result += maxhp*maxHPDamage;
    }
    if (currentHPDamage != 0.0)
    {
        result += hp*currentHPDamage;
    }
    if (executeHPDamage != 0.0)
    {
        result += (maxhp-hp)*executeHPDamage;
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

DamageEffect Shop::upgrade(DamageEffect dmg, QString effect)
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
    if (effect == "armpen" && levels["armpen"] < 7)
    {
        dmg.armpen += items["armpen"].at(levels["armpen"]);
        levels["armpen"] += 1;
        return dmg;
    }
    if (effect == "crit" && levels["crit"] < 7)
    {
        dmg.critChance = items["critchance"].at(levels["crit"]);
        dmg.critMod = items["critmod"].at(levels["crit"]);
        levels["crit"] += 1;
        return dmg;
    }
    if (effect == "currenthpdamage" && levels["currenthpdamage"] < 7)
    {
        dmg.currentHPDamage = items["currenthpdamage"].at(levels["currenthpdamage"]);
        levels["currenthpdamage"] += 1;
        return dmg;
    }
    if (effect == "maxhpdamage" && levels["maxhpdamage"] < 7)
    {
        dmg.maxHPDamage = items["maxhpdamage"].at(levels["maxhpdamage"]);
        levels["maxhpdamage"] += 1;
        return dmg;
    }
    if (effect == "executehpdamage" && levels["executehpdamage"] < 7)
    {
        dmg.executeHPDamage = items["executehpdamage"].at(levels["executehpdamage"]);
        levels["executehpdamage"] += 1;
        return dmg;
    }
    if (effect == "onhit" && levels["onhit"] < 7)
    {
        dmg.onhitChance = items["onhitchance"].at(levels["onhit"]);
        dmg.onhitDamage = items["onhitdamage"].at(levels["onhit"]);
        levels["onhit"] += 1;
        return dmg;
    }
    if (effect == "percentarmpen" && levels["percentarmpen"] < 7)
    {
        dmg.percentArmpen = items["percentarmpen"].at(levels["percentarmpen"]);
        levels["percentarmpen"] += 1;
        return dmg;
    }
    if (effect == "splash" && levels["splash"] < 7)
    {
        dmg.splash = items["splash"].at(levels["splash"]);
        levels["splash"] += 1;
        return dmg;
    }
    if (effect == "dmgincrease" && levels["dmgincrease"] < 7)
    {
        dmg.value += items["dmgincrease"].at(levels["dmgincrease"]);
        levels["dmgincrease"] += 1;
        return dmg;
    }
    return dmg;

}
