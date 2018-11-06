SECTIONS
{
	/* Common sections */
	. = 0x8000000;
	.rom : {rom.o(.rom)}
	. = 0x8800000;	
	.text : {*(.text)}
	.rodata : {*(.rodata)}
	
	/* Custom sections */
	. = 0x8000BC0;
	.random : {lucky.o(.random)}
	. = 0x8024D60;
	.calculateBattleDamage : {lucky.o(.calculateBattleDamage)}
	
	/* Global variables */
	forceFlag = 0x2039201;
	damage = 0x2039202;
	attack = 0x2039204;
	defence = 0x2039206;
	hitRate = 0x2039208;
	criticalRate = 0x203920A;
	battleFlag = 0x2039328;
	
	/* Vanilla functions */
	ifHappenDoubleRNWrapper = 0x80243A1;
	ifHappenSingleRNWrapper = 0x80243CD;
}