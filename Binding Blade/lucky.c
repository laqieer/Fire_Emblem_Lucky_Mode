// created by laqieer
// 2018/11/6

#include "../type.h"

// Global variables
extern __int16 damage;
extern __int16 attack;
extern __int16 defence;
extern __int16 hitRate;
extern __int16 criticalRate;
extern char forceFlag;
extern _WORD *battleFlag;

// Vanilla functions
int ifHappenDoubleRNWrapper(u16 pr, u8 force);
int ifHappenSingleRNWrapper(u16 pr, u8 force);

int ifEnemyAttack(u8 battleData[])
{
	return battleData[0xB] >= 0x80 && battleData[0xB] < 0xC0;
}

__attribute__((section(".random")))
int random()
{
	return 0;
}

void calculateBattleDamage(u8 battleData[])
{
	damage = 0;
	//if ( ifHappenDoubleRNWrapper(hitRate, 1) << 24 )
	if ( ifHappenDoubleRNWrapper(hitRate, 1u) << 24 && !(ifEnemyAttack(battleData) && hitRate < 100 && !(forceFlag & 2)))
	{
		damage = attack - defence;
		//if ( (char)ifHappenSingleRNWrapper(criticalRate, 0) == 1 )
		if ( (char)ifHappenSingleRNWrapper(criticalRate, 0) == 1  && !(ifEnemyAttack(battleData) && criticalRate < 100 && !(forceFlag & 2)))
		{
			*battleFlag |= 1u;
			damage *= 3;
		}
		if ( damage > 99 )
			damage = 99;
		if ( damage < 0 )
			damage = 0;
		if ( damage )
			battleData[120] = 1;
	}
	else
	{
		*battleFlag |= 2u;
	}
}

__attribute__((section(".calculateBattleDamage")))
void calculateBattleDamageWrapper(u8 battleData[])
{
	calculateBattleDamage(battleData);
}