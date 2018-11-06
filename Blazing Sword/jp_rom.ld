SECTIONS
{
	/* Common sections */
	. = 0x8000000;
	.rom : {jp_rom.o(.rom)}
	. = 0x9000000;	
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	
	/* Custom sections */
	. = 0x8000BB8;
	.random : {lucky.o(.random)}
	. = 0x8029714;
	.calculateBattleDamage : {lucky.o(.calculateBattleDamage)}
	/*. = 0x802984C;
	.handleWeaponEffect : {lucky.o(.handleWeaponEffect)}*/
	. = 0x80298A4;
	.weaponEffectID_devilReversal : {lucky.o(.weaponEffectID_devilReversal)}
	
	/* Global variables */
	forceFlag = 0x203A3D4;
	damage = 0x203A3D8;
	attack = 0x203A3DA;
	defence = 0x203A3DC;
	hitRate = 0x203A3DE;
	criticalRate = 0x203A3E0;
	instantKillRate = 0x203A3E2;
	dataOffensiveSide = 0x203A3EC;
	dataDefensiveSide = 0x203A46C;
	battleFlag = 0x203A508;
	
	/* Vanilla functions */
	ifHappenDoubleRNWrapper = 0x8028A35;
	ifHappenSingleRNWrapper = 0x8028A09;
	getWeaponEffect = 0x801782D;
	sub_8016B90 = 0x8016B91;
}