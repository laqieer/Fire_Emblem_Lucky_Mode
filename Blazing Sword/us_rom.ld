SECTIONS
{
	/* Common sections */
	. = 0x8000000;
	.rom : {us_rom.o(.rom)}
	. = 0x9000000;	
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	
	/* Custom sections */
	. = 0x8000BE0;
	.random : {lucky.o(.random)}
	. = 0x8029264;
	.calculateBattleDamage : {lucky.o(.calculateBattleDamage)}
	/*. = 0x802939C;
	.handleWeaponEffect : {lucky.o(.handleWeaponEffect)}*/
	
	/* Global variables */
	forceFlag = 0x203A3D8;
	damage = 0x203A3DC;
	attack = 0x203A3DE;
	defence = 0x203A3E0;
	hitRate = 0x203A3E2;
	criticalRate = 0x203A3E4;
	instantKillRate = 0x203A3E6;
	dataOffensiveSide = 0x203A3F0;
	dataDefensiveSide = 0x203A470;
	battleFlag = 0x203A50C;
	
	/* Vanilla functions */
	ifHappenDoubleRNWrapper = 0x80285A9;
	ifHappenSingleRNWrapper = 0x802857D;
	getWeaponEffect = 0x801722C;
	sub_8016B90 = 0x8016731;
}