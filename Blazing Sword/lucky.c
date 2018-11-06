// created by laqieer
// 2018/11/5

#include "../type.h"

typedef enum WeaponEffect
{
	WeaponEffect_NULL = 0,
	WeaponEffect_Poison,
	WeaponEffect_StealHP,
	WeaponEffect_HalveHP,
	WeaponEffect_DevilReversal
} WeaponEffect;

// Global variables
extern __int16 damage;
extern __int16 attack;
extern __int16 defence;
extern __int16 hitRate;
extern __int16 criticalRate;
extern __int16 instantKillRate;
extern __int16 forceFlag;
extern u8 dataOffensiveSide[];
extern u8 dataDefensiveSide[];
extern _WORD *battleFlag;

// Vanilla functions
int ifHappenDoubleRNWrapper(u16 pr, u8 force);
int ifHappenSingleRNWrapper(u16 pr, u8 force);
WeaponEffect getWeaponEffect(u16 weapon);
int sub_8016B90(int weapon);

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
	//if ( ifHappenDoubleRNWrapper(hitRate, 1u) << 24 )
	if ( ifHappenDoubleRNWrapper(hitRate, 1u) << 24 && !(ifEnemyAttack(battleData) && hitRate < 100 && !(forceFlag & 2)))
	{
		damage = attack - defence;
		//if ( (char)ifHappenSingleRNWrapper(criticalRate, 0) == 1 )
		if ( (char)ifHappenSingleRNWrapper(criticalRate, 0) == 1  && !(ifEnemyAttack(battleData) && criticalRate < 100 && !(forceFlag & 2)))
		{
			//if ( (char)ifHappenSingleRNWrapper(instantKillRate, 0) == 1 )
			if ( (char)ifHappenSingleRNWrapper(instantKillRate, 0) == 1 && !(ifEnemyAttack(battleData) && instantKillRate < 100 && !(forceFlag & 2)))
			{
				*battleFlag |= 0x800u;
				damage = 127;
			}
			else
			{
				*battleFlag |= 1u;
				damage = 3 * damage;
			}
		}
		if ( damage > 127 )
			damage = 127;
		if ( damage < 0 )
			damage = 0;
		if ( damage )
			battleData[124] = 1;
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

//FIXME : No Damage Bug
void handleWeaponEffect(u8 dataAttacker[], u8 dataDefender[])
{
	WeaponEffect weaponEffect;
	_WORD *battleFlag;
	s16 v7;
	u8 attackerHP;
	int defenderHP;
	int dmg;
	int v13;
	int v14;

	++dataAttacker[123];
	if ( *battleFlag & 2 )
		goto LABEL_20;
	weaponEffect = getWeaponEffect(*((u16 *)dataAttacker + 36));
	if ( weaponEffect == WeaponEffect_Poison )
	{
		dataDefender[111] = 1;
		v7 = 64;
LABEL_7:
		*battleFlag |= v7;
		goto LABEL_8;
	}
	if ( weaponEffect == WeaponEffect_HalveHP )
	{
		v7 = 512;
		goto LABEL_7;
	}
LABEL_8:
	if ( weaponEffect == WeaponEffect_DevilReversal
		&& ifHappenSingleRNWrapper(31 - (char)dataAttacker[25], 0) << 24 )
	{
		*battleFlag |= 0x80u;
		attackerHP = dataAttacker[19] - damage;
		dataAttacker[19] = attackerHP;
		if ( attackerHP & 0x80 )
			dataAttacker[19] = 0;
	}
	else
	{
		defenderHP = (char)dataDefender[19];
		if ( damage > defenderHP )
			damage = defenderHP;
		//defenderHP = dataDefender[19];
		//dmg = (u8)damage;
		dataDefender[19] = defenderHP - damage;
		//if ( (defenderHP - dmg) & 0x80 )
		//if ( defenderHP - damage < 0 )
			//dataDefender[19] = 0;
	}
	if ( weaponEffect == WeaponEffect_StealHP )
	{
		attackerHP = dataAttacker[19] + (u8)damage;
		dataAttacker[19] = attackerHP;
		v13 = dataAttacker[18];
		if ( attackerHP << 24 > v13 << 24 )
			dataAttacker[19] = v13;
		*battleFlag |= 0x100u;
	}
LABEL_20:
	*(_BYTE *)(*(int *)battleFlag + 3) = damage;
	if ( !(*battleFlag & 2) || *((_DWORD *)dataAttacker + 19) & 0x82 )
	{
		v14 = sub_8016B90(*((u16 *)dataAttacker + 36));
		*((_WORD *)dataAttacker + 36) = v14;
		if ( !(v14 << 16) )
			dataAttacker[125] = 1;
	}
}

/*
void handleWeaponEffect(u8 dataAttacker[], u8 dataDefender[])
{
	WeaponEffect weaponEffect;
	u16 weapon;
	
	++dataAttacker[123];
	weapon = *((u16 *)dataAttacker + 36);
	weaponEffect = getWeaponEffect(weapon);
	if ( *battleFlag & 2 == 0)
	{
		if ( damage > dataDefender[19])
			damage = dataDefender[19];
		dataDefender[19] -= damage;
	}
	
	*(_BYTE *)(*(int *)battleFlag + 3) = damage;
	if ( !(*battleFlag & 2) || *((_DWORD *)dataAttacker + 19) & 0x82 )
	{
		*((_WORD *)dataAttacker + 36) =  sub_8016B90(weapon);
		if ( !(*((_WORD *)dataAttacker + 36) << 16) )
			dataAttacker[125] = 1;
	}
}
*/

__attribute__((section(".handleWeaponEffect")))
void handleWeaponEffectWrapper(u8 dataAttacker[], u8 dataDefender[])
{
	handleWeaponEffect(dataAttacker, dataDefender);
}
