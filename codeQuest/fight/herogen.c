#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define CONST_DEFENCE 10000

#define MAJOR_STAT_MAX 1000
#define MAJOR_STAT_MIN 600
#define MINOR_STAT_MAX 500
#define MINOR_STAT_MIN 300
#define HP_KNIGHT_MAX 21000
#define HP_KNIGHT_MIN 16000
#define HP_WARRIOR_MAX 17000
#define HP_WARRIOR_MIN 14000
#define HP_ARCHER_MAX 13000
#define HP_ARCHER_MIN 11000
#define HP_ASSASSIN_MAX 13000
#define HP_ASSASSIN_MIN 11000

#define PLATE_ARMOR 1
#define LEATHER_ARMOR 2
#define ONEHAND_SWORD 3
#define TWOHAND_SWORD 4
#define SHORT_SWORD 5
#define SHIELD 6
#define BOW 7

#define ITEM_PLATEARMOR_DEFENCE_MAX 6000
#define ITEM_PLATEARMOR_DEFENCE_MIN 3000
#define ITEM_LEATHERARMOR_DEFENCE_MAX 3000
#define ITEM_LEATHERARMOR_DEFENCE_MIN 1500

#define ITEM_MAJORARMOR_MAX 1200
#define ITEM_MAJORARMOR_MIN 600
#define ITEM_MINORARMOR_MAX 600
#define ITEM_MINORARMOR_MIN 300
#define ITEM_EVASION_MAX 250
#define ITEM_EVASION_MIN 60
#define ITEM_HEALTHPOINT_MAX 2000
#define ITEM_HEALTHPOINT_MIN 500

#define ITEM_ONEHAND_SWORD_STRENGTH_MAX 400
#define ITEM_ONEHAND_SWORD_STRENGTH_MIN 200
#define ITEM_ONEHAND_SWORD_CRITICAL_RATIO_MAX 150
#define ITEM_ONEHAND_SWORD_CRITICAL_RATIO_MIN 60
#define ITEM_ONEHAND_SWORD_CRITICAL_POWER_MAX 40
#define ITEM_ONEHAND_SWORD_CRITICAL_POWER_MIN 20
#define ITEM_ONEHAND_SWORD_PIERCING_MAX 40
#define ITEM_ONEHAND_SWORD_PIERCING_MIN 20
#define ITEM_ONEHAND_ATTACK_POWER_MAX 1200
#define ITEM_ONEHAND_ATTACK_POWER_MIN 700
#define ITEM_ONEHAND_ACCURACY_MAX 253
#define ITEM_ONEHAND_ACCURACY_MIN 70

#define ITEM_TWOHAND_SWORD_STRENGTH_MAX 700
#define ITEM_TWOHAND_SWORD_STRENGTH_MIN 400
#define ITEM_TWOHAND_SWORD_CRITICAL_RATIO_MAX 300
#define ITEM_TWOHAND_SWORD_CRITICAL_RATIO_MIN 120
#define ITEM_TWOHAND_SWORD_CRITICAL_POWER_MAX 40
#define ITEM_TWOHAND_SWORD_CRITICAL_POWER_MIN 20
#define ITEM_TWOHAND_SWORD_PIERCING_MAX 60
#define ITEM_TWOHAND_SWORD_PIERCING_MIN 30
#define ITEM_TWOHAND_ATTACK_POWER_MAX 2300
#define ITEM_TWOHAND_ATTACK_POWER_MIN 1300
#define ITEM_TWOHAND_ACCURACY_MAX 200
#define ITEM_TWOHAND_ACCURACY_MIN 30

#define ITEM_SHORT_SWORD_DEXERITY_MAX 400
#define ITEM_SHORT_SWORD_DEXERITY_MIN 200
#define ITEM_SHORT_SWORD_CRITICAL_RATIO_MAX 170
#define ITEM_SHORT_SWORD_CRITICAL_RATIO_MIN 80
#define ITEM_SHORT_SWORD_CRITICAL_POWER_MAX 40
#define ITEM_SHORT_SWORD_CRITICAL_POWER_MIN 15
#define ITEM_SHORT_SWORD_PIERCING_MAX 60
#define ITEM_SHORT_SWORD_PIERCING_MIN 40
#define ITEM_SHORT_SWORD_ATTACK_POWER_MAX 1100
#define ITEM_SHORT_SWORD_ATTACK_POWER_MIN 700
#define ITEM_SHORT_SWORD_ACCURACY_MAX 133
#define ITEM_SHORT_SWORD_ACCURACY_MIN 90

#define ITEM_BOW_DEXERITY_MAX 700
#define ITEM_BOW_DEXERITY_MIN 400
#define ITEM_BOW_CRITICAL_RATIO_MAX 400
#define ITEM_BOW_CRITICAL_RATIO_MIN 160
#define ITEM_BOW_CRITICAL_POWER_MAX 90
#define ITEM_BOW_CRITICAL_POWER_MIN 40
#define ITEM_BOW_PIERCING_MAX 100
#define ITEM_BOW_PIERCING_MIN 60
#define ITEM_BOW_ATTACK_POWER_MAX 2400
#define ITEM_BOW_ATTACK_POWER_MIN 1000
#define ITEM_BOW_ACCURACY_MAX 200
#define ITEM_BOW_ACCURACY_MIN 50

#define ITEM_SHIELD_DEFENCE_MAX 4500
#define ITEM_SHIELD_DEFENCE_MIN 3000
#define ITEM_SHIELD_RANGE_BLOCKING_MAX 40
#define ITEM_SHIELD_RANGE_BLOCKING_MIN 20
#define ITEM_SHIELD_MELEE_BLOCKING_MAX 60
#define ITEM_SHIELD_MELEE_BLOCKING_MIN 30
#define ITEM_SHIELD_STRENGTH_MAX 400
#define ITEM_SHIELD_STRENGTH_MIN 200

#define KNIGHT 1
#define WARRIOR 2
#define ARCHER 3
#define ASSASSIN 4

typedef struct attribute {
	int attackPower;
	int accuracy;
	int criticalPower;
	int criticalRatio;
	int piercingArmor;
	int defence;
	int evasion;
	int rangeBlocking;
	int meleeBlocking;
	int strength;
	int dexerity;
	int healthPoint;
} ATTRIBUTE;

typedef struct character {
	int class;
	ATTRIBUTE armor;
	ATTRIBUTE rightHand;
	ATTRIBUTE leftHand;
	ATTRIBUTE charecterAttr;
} CHARACTER;

void initRandom(){
	time_t t;
	srand((unsigned)time(&t));
}

int getRandom(int min, int max){
	return min + (rand() % ((max + 1) - min));
}

void flush(){
	while(getchar() != '\n');
}

void showTitle(){
	system("clear");
	printf("%c[33m┌─────────────────────────────────────────────────┐\n", 27);
	printf("│                  %c[36mHero Generator%c[33m                 │\n", 27, 27);
	printf("└─────────────────────────────────────────────────┘%c[0m\n", 27);
}

void weaponGenerator(ATTRIBUTE *item, int class){
	if(class == PLATE_ARMOR){
		item->defence = getRandom(ITEM_PLATEARMOR_DEFENCE_MIN, ITEM_PLATEARMOR_DEFENCE_MAX);
		item->strength = getRandom(ITEM_MAJORARMOR_MIN, ITEM_MAJORARMOR_MAX);
		item->dexerity = getRandom(ITEM_MINORARMOR_MIN, ITEM_MINORARMOR_MAX);
		item->healthPoint = getRandom(ITEM_HEALTHPOINT_MIN, ITEM_HEALTHPOINT_MAX);
	} else if(class == LEATHER_ARMOR){
		item->defence = getRandom(ITEM_LEATHERARMOR_DEFENCE_MIN, ITEM_LEATHERARMOR_DEFENCE_MAX);
		item->strength = getRandom(ITEM_MINORARMOR_MIN, ITEM_MINORARMOR_MAX);
		item->dexerity = getRandom(ITEM_MAJORARMOR_MIN, ITEM_MAJORARMOR_MAX);
		item->evasion = getRandom(ITEM_EVASION_MIN, ITEM_EVASION_MAX);
		item->healthPoint = getRandom(ITEM_HEALTHPOINT_MIN, ITEM_HEALTHPOINT_MAX);
	} else if(class == ONEHAND_SWORD){
		item->strength = getRandom(ITEM_ONEHAND_SWORD_STRENGTH_MIN, ITEM_ONEHAND_SWORD_STRENGTH_MAX);
		item->attackPower = getRandom(ITEM_ONEHAND_ATTACK_POWER_MIN, ITEM_ONEHAND_ATTACK_POWER_MAX);
		item->accuracy = getRandom(ITEM_ONEHAND_ACCURACY_MIN, ITEM_ONEHAND_ACCURACY_MAX);
		item->criticalRatio = getRandom(ITEM_ONEHAND_SWORD_CRITICAL_RATIO_MIN, ITEM_ONEHAND_SWORD_CRITICAL_RATIO_MAX);
		item->criticalPower = getRandom(ITEM_ONEHAND_SWORD_CRITICAL_POWER_MIN, ITEM_ONEHAND_SWORD_CRITICAL_POWER_MAX);
		item->piercingArmor = getRandom(ITEM_ONEHAND_SWORD_PIERCING_MIN, ITEM_ONEHAND_SWORD_PIERCING_MAX);
	} else if(class == TWOHAND_SWORD){
		item->strength = getRandom(ITEM_TWOHAND_SWORD_STRENGTH_MIN, ITEM_TWOHAND_SWORD_STRENGTH_MAX);
		item->attackPower = getRandom(ITEM_TWOHAND_ATTACK_POWER_MIN, ITEM_TWOHAND_ATTACK_POWER_MAX);
		item->accuracy = getRandom(ITEM_TWOHAND_ACCURACY_MIN, ITEM_TWOHAND_ACCURACY_MAX);
		item->criticalRatio = getRandom(ITEM_TWOHAND_SWORD_CRITICAL_RATIO_MIN, ITEM_TWOHAND_SWORD_CRITICAL_RATIO_MAX);
		item->criticalPower = getRandom(ITEM_TWOHAND_SWORD_CRITICAL_POWER_MIN, ITEM_TWOHAND_SWORD_CRITICAL_POWER_MAX);
		item->piercingArmor = getRandom(ITEM_TWOHAND_SWORD_PIERCING_MIN, ITEM_TWOHAND_SWORD_PIERCING_MAX);
	} else if(class == SHORT_SWORD){
		item->dexerity = getRandom(ITEM_SHORT_SWORD_DEXERITY_MIN, ITEM_SHORT_SWORD_DEXERITY_MAX);
		item->attackPower = getRandom(ITEM_SHORT_SWORD_ATTACK_POWER_MIN, ITEM_SHORT_SWORD_ATTACK_POWER_MAX);
		item->accuracy = getRandom(ITEM_SHORT_SWORD_ACCURACY_MIN, ITEM_SHORT_SWORD_ACCURACY_MAX);
		item->criticalRatio = getRandom(ITEM_SHORT_SWORD_CRITICAL_RATIO_MIN, ITEM_SHORT_SWORD_CRITICAL_RATIO_MAX);
		item->criticalPower = getRandom(ITEM_SHORT_SWORD_CRITICAL_POWER_MIN, ITEM_SHORT_SWORD_CRITICAL_POWER_MAX);
		item->piercingArmor = getRandom(ITEM_SHORT_SWORD_PIERCING_MIN, ITEM_SHORT_SWORD_PIERCING_MAX);
	} else if(class == BOW) {
		item->dexerity = getRandom(ITEM_BOW_DEXERITY_MIN, ITEM_BOW_DEXERITY_MAX);
		item->attackPower = getRandom(ITEM_BOW_ATTACK_POWER_MIN, ITEM_BOW_ATTACK_POWER_MAX);
		item->accuracy = getRandom(ITEM_BOW_ACCURACY_MIN, ITEM_BOW_ACCURACY_MAX);
		item->criticalRatio = getRandom(ITEM_BOW_CRITICAL_RATIO_MIN, ITEM_BOW_CRITICAL_RATIO_MAX);
		item->criticalPower = getRandom(ITEM_BOW_CRITICAL_POWER_MIN, ITEM_BOW_CRITICAL_POWER_MAX);
		item->piercingArmor = getRandom(ITEM_BOW_PIERCING_MIN, ITEM_BOW_PIERCING_MAX);
	} else if(class == SHIELD){
		item->strength = getRandom(ITEM_SHIELD_STRENGTH_MIN, ITEM_SHIELD_STRENGTH_MAX);
		item->defence = getRandom(ITEM_SHIELD_DEFENCE_MIN, ITEM_SHIELD_DEFENCE_MAX);
		item->rangeBlocking = getRandom(ITEM_SHIELD_RANGE_BLOCKING_MIN, ITEM_SHIELD_RANGE_BLOCKING_MAX);
		item->meleeBlocking = getRandom(ITEM_SHIELD_MELEE_BLOCKING_MIN, ITEM_SHIELD_MELEE_BLOCKING_MAX);
	}		
}

void generator(CHARACTER *heroes, int class){
	if(class == KNIGHT){			//knight
		heroes->class = KNIGHT;
		heroes->charecterAttr.strength = getRandom(MAJOR_STAT_MIN, MAJOR_STAT_MAX);
		heroes->charecterAttr.dexerity = getRandom(MINOR_STAT_MIN, MINOR_STAT_MAX);
		heroes->charecterAttr.healthPoint = getRandom(HP_KNIGHT_MIN, HP_KNIGHT_MAX);
		weaponGenerator(&heroes->armor, PLATE_ARMOR);
		weaponGenerator(&heroes->rightHand, ONEHAND_SWORD);
		weaponGenerator(&heroes->leftHand, SHIELD);
	} else if(class == WARRIOR){	//warrior
		heroes->class = WARRIOR;
		heroes->charecterAttr.strength = getRandom(MAJOR_STAT_MIN, MAJOR_STAT_MAX);
		heroes->charecterAttr.dexerity = getRandom(MINOR_STAT_MIN, MINOR_STAT_MAX);
		heroes->charecterAttr.healthPoint = getRandom(HP_WARRIOR_MIN, HP_WARRIOR_MAX);
		weaponGenerator(&heroes->armor, PLATE_ARMOR);
		weaponGenerator(&heroes->rightHand, TWOHAND_SWORD);
	} else if(class == ARCHER){	//warrior
		heroes->class = ARCHER;
		heroes->charecterAttr.strength = getRandom(MINOR_STAT_MIN, MINOR_STAT_MAX);
		heroes->charecterAttr.dexerity = getRandom(MAJOR_STAT_MIN, MAJOR_STAT_MAX);
		heroes->charecterAttr.healthPoint = getRandom(HP_ARCHER_MIN, HP_ARCHER_MAX);
		weaponGenerator(&heroes->armor, LEATHER_ARMOR);
		weaponGenerator(&heroes->rightHand, BOW);
	} else if(class == ASSASSIN){	//warrior
		heroes->class = ASSASSIN;
		heroes->charecterAttr.strength = getRandom(MINOR_STAT_MIN, MINOR_STAT_MAX);
		heroes->charecterAttr.dexerity = getRandom(MAJOR_STAT_MIN, MAJOR_STAT_MAX);
		heroes->charecterAttr.healthPoint = getRandom(HP_ASSASSIN_MIN, HP_ASSASSIN_MAX);
		weaponGenerator(&heroes->armor, LEATHER_ARMOR);
		weaponGenerator(&heroes->rightHand, SHORT_SWORD);
		weaponGenerator(&heroes->leftHand, SHORT_SWORD);
	}
	double dex;
	double str;
	double hp;
	double attackPower;
	double accuracy;
	double criticalRatio;
	double criticalPower;
	double defence;
	double evasion;
	double rangeBlocking;
	double meleeBlocking;
	double piercingArmor;

	dex = heroes->charecterAttr.dexerity + heroes->armor.dexerity + heroes->rightHand.dexerity + heroes->leftHand.dexerity;
	str = heroes->charecterAttr.strength + heroes->armor.strength + heroes->rightHand.strength + heroes->leftHand.strength;
	hp = heroes->charecterAttr.healthPoint + heroes->armor.healthPoint;
	attackPower = heroes->armor.attackPower + heroes->rightHand.attackPower + heroes->leftHand.attackPower;
	accuracy = heroes->armor.accuracy + heroes->rightHand.accuracy + heroes->leftHand.accuracy;
	criticalRatio = heroes->armor.criticalRatio + heroes->rightHand.criticalRatio + heroes->leftHand.criticalRatio;
	criticalPower = heroes->armor.criticalPower + heroes->rightHand.criticalPower + heroes->leftHand.criticalPower;
	piercingArmor = heroes->rightHand.piercingArmor + heroes->leftHand.piercingArmor;
	defence = heroes->armor.defence + heroes->leftHand.defence;
	evasion = heroes->armor.evasion + heroes->leftHand.evasion;
	rangeBlocking = heroes->leftHand.rangeBlocking;
	meleeBlocking = heroes->leftHand.meleeBlocking;
	
	if(class == KNIGHT || class == WARRIOR){
		heroes->charecterAttr.attackPower = (int)(round(dex * 0.6) + attackPower);
	} else if (class == ARCHER || class == ASSASSIN){
		heroes->charecterAttr.attackPower = (int)(round(str * 0.6) + attackPower);
	}
	heroes->charecterAttr.accuracy = accuracy + (1000 - (4000 / pow((double)dex,0.4)));
	heroes->charecterAttr.criticalRatio = criticalRatio + (dex / 60);
	heroes->charecterAttr.criticalPower = criticalPower + (pow((double)str, 0.5) / 10);
	heroes->charecterAttr.piercingArmor = piercingArmor + (pow((double)dex, 0.5) / 10);
	heroes->charecterAttr.defence = defence + ((str * 2 + dex * 1.2) / 2);
	heroes->charecterAttr.evasion = evasion + (pow((double)dex, 0.5) / 2);
	heroes->charecterAttr.rangeBlocking = rangeBlocking;
	heroes->charecterAttr.meleeBlocking = meleeBlocking;
	heroes->charecterAttr.dexerity = dex;
	heroes->charecterAttr.strength = str;
	heroes->charecterAttr.healthPoint = hp;
}

void showBar(int max, int current){
	int i = 0;
	printf("%c[32m",27);
	for(i = 0; i < 10; i++){
		if(round((current * 10) / max) > i){
			printf("■");
		} else {
			printf("□");
		}		
	}
	printf("%c[0m",27);
}

void structInit(CHARACTER *heroes){
	heroes->class = 0;
	heroes->armor.attackPower = 0;
	heroes->armor.accuracy = 0;
	heroes->armor.criticalPower = 0;
	heroes->armor.criticalRatio = 0;
	heroes->armor.piercingArmor = 0;
	heroes->armor.defence = 0;
	heroes->armor.evasion = 0;
	heroes->armor.rangeBlocking = 0;
	heroes->armor.meleeBlocking = 0;
	heroes->armor.strength = 0;
	heroes->armor.dexerity = 0;
	heroes->armor.healthPoint = 0;
	heroes->rightHand.attackPower = 0;
	heroes->rightHand.accuracy = 0;
	heroes->rightHand.criticalPower = 0;
	heroes->rightHand.criticalRatio = 0;
	heroes->rightHand.piercingArmor = 0;
	heroes->rightHand.defence = 0;
	heroes->rightHand.evasion = 0;
	heroes->rightHand.rangeBlocking = 0;
	heroes->rightHand.meleeBlocking = 0;
	heroes->rightHand.strength = 0;
	heroes->rightHand.dexerity = 0;
	heroes->rightHand.healthPoint = 0;
	heroes->leftHand.attackPower = 0;
	heroes->leftHand.accuracy = 0;
	heroes->leftHand.criticalPower = 0;
	heroes->leftHand.criticalRatio = 0;
	heroes->leftHand.piercingArmor = 0;
	heroes->leftHand.defence = 0;
	heroes->leftHand.evasion = 0;
	heroes->leftHand.rangeBlocking = 0;
	heroes->leftHand.meleeBlocking = 0;
	heroes->leftHand.strength = 0;
	heroes->leftHand.dexerity = 0;
	heroes->leftHand.healthPoint = 0;
}

void showHero(CHARACTER *heroes){
	char class[10] = {};
	int hpMax;
	int strMax;
	int dexMax;
	if(heroes->class == KNIGHT) {
		strcpy(class, "Knight");
		hpMax = HP_KNIGHT_MAX + ITEM_HEALTHPOINT_MAX;
		strMax = MAJOR_STAT_MAX + ITEM_ONEHAND_SWORD_STRENGTH_MAX + ITEM_SHIELD_STRENGTH_MAX + ITEM_MAJORARMOR_MAX;
		dexMax = MINOR_STAT_MAX + ITEM_MINORARMOR_MAX;
	}
	if(heroes->class == WARRIOR) {
		strcpy(class, "Warrior");
		hpMax = HP_WARRIOR_MAX + ITEM_HEALTHPOINT_MAX;
		strMax = MAJOR_STAT_MAX + ITEM_TWOHAND_SWORD_STRENGTH_MAX + ITEM_MAJORARMOR_MAX;
		dexMax = MINOR_STAT_MAX + ITEM_MINORARMOR_MAX;
	}
	if(heroes->class == ARCHER) {
		strcpy(class, "Archer");
		hpMax = HP_ARCHER_MAX + ITEM_HEALTHPOINT_MAX;
		strMax = MINOR_STAT_MAX + ITEM_MINORARMOR_MAX;
		dexMax = MAJOR_STAT_MAX + ITEM_BOW_DEXERITY_MAX + ITEM_MAJORARMOR_MAX;
	}
	if(heroes->class == ASSASSIN) {
		strcpy(class, "Assassin");
		hpMax = HP_ASSASSIN_MAX + ITEM_HEALTHPOINT_MAX;
		strMax = MINOR_STAT_MAX + ITEM_MINORARMOR_MAX;
		dexMax = MAJOR_STAT_MAX + ITEM_SHORT_SWORD_DEXERITY_MAX + ITEM_SHORT_SWORD_DEXERITY_MAX + ITEM_MAJORARMOR_MAX;
	}

	printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	printf("%c[31mCLASS: %s\n%c[30m", 27,class,27);
	printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	printf("Strength:");showBar(strMax,heroes->charecterAttr.strength);printf("%d/%d\t", heroes->charecterAttr.strength, strMax);
	printf(" Attack Power: %d\t", heroes->charecterAttr.attackPower);
	printf(" Piercing : %d\n", heroes->charecterAttr.piercingArmor);
	
	printf("Dexerity:");showBar(dexMax,heroes->charecterAttr.dexerity);printf("%d/%d\t", heroes->charecterAttr.dexerity, dexMax);
	printf(" Accuracy    : %d\t", heroes->charecterAttr.accuracy);
	printf(" Evasion  : %d\n", heroes->charecterAttr.evasion);
	
	printf("HP      :");showBar(hpMax,heroes->charecterAttr.healthPoint - heroes->armor.healthPoint);printf("%d/%d\t", (heroes->charecterAttr.healthPoint - heroes->armor.healthPoint), hpMax);
	printf(" CRIT Ratio  : %d\t", heroes->charecterAttr.criticalRatio);
	printf(" Range BLK: %d\n", heroes->charecterAttr.rangeBlocking);
	
	printf("Defence : %d\t\t\t", heroes->charecterAttr.defence);
	printf(" CRIT Power  : %d\t", heroes->charecterAttr.criticalPower);
	printf(" Melee BLK: %d\n", heroes->charecterAttr.meleeBlocking);
	
	printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	if(heroes->class == KNIGHT) {
		printf("Armor\t\t\tOne hand sword\t\tShield\n");
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
		printf("Defence  : %d\t\t",heroes->armor.defence);		printf("Attack Power: %d  \t",heroes->rightHand.attackPower);	printf("Defence     : %d\n",heroes->leftHand.defence);
		printf("Evasion  : %d\t\t",heroes->armor.evasion);		printf("Strength    : %d  \t",heroes->rightHand.strength);		printf("Strength    : %d\n",heroes->leftHand.strength);
		printf("HP       : %d\t\t",heroes->armor.healthPoint);	printf("Accuracy    : %d  \t",heroes->rightHand.accuracy);		printf("Range Block : %d\n",heroes->leftHand.rangeBlocking);
		printf("Strength : %d\t\t",heroes->armor.strength);		printf("CRIT Power  : %d  \t",heroes->rightHand.criticalPower);	printf("Melee Block : %d\n",heroes->leftHand.meleeBlocking);
		printf("Dexerity : %d\t\t",heroes->armor.dexerity);		printf("CRIT Ratio  : %d\n",heroes->rightHand.criticalRatio);
		printf("\t\t\t");										printf("Piercing    : %d\n",heroes->rightHand.piercingArmor);
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	}
	if(heroes->class == WARRIOR) {
		printf("Armor\t\t\tTwo hand sword\n");
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
		printf("Defence  : %d\t\t",heroes->armor.defence);		printf("Attack Power: %d\n",heroes->rightHand.attackPower);
		printf("Evasion  : %d\t\t",heroes->armor.evasion);		printf("Strength    : %d\n",heroes->rightHand.strength);
		printf("HP       : %d\t\t",heroes->armor.healthPoint);	printf("Accuracy    : %d\n",heroes->rightHand.accuracy);
		printf("Strength : %d\t\t",heroes->armor.strength);		printf("CRIT Power  : %d\n",heroes->rightHand.criticalPower);
		printf("Dexerity : %d\t\t",heroes->armor.dexerity);		printf("CRIT Ratio  : %d\n",heroes->rightHand.criticalRatio);
		printf("\t\t\t");										printf("Piercing    : %d\n",heroes->rightHand.piercingArmor);
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	}
	if(heroes->class == ARCHER) {
		printf("Armor\t\t\tBow\n");
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
		printf("Defence  : %d\t\t",heroes->armor.defence);		printf("Attack Power: %d\n",heroes->rightHand.attackPower);
		printf("Evasion  : %d\t\t",heroes->armor.evasion);		printf("Dexerity    : %d\n",heroes->rightHand.dexerity);
		printf("HP       : %d\t\t",heroes->armor.healthPoint);	printf("Accuracy    : %d\n",heroes->rightHand.accuracy);
		printf("Strength : %d\t\t",heroes->armor.strength);		printf("CRIT Power  : %d\n",heroes->rightHand.criticalPower);
		printf("Dexerity : %d\t\t",heroes->armor.dexerity);		printf("CRIT Ratio  : %d\n",heroes->rightHand.criticalRatio);
		printf("\t\t\t");										printf("Piercing    : %d\n",heroes->rightHand.piercingArmor);
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	}
	if(heroes->class == ASSASSIN) {
		printf("Armor\t\t\tRight Short sword\tLeft Short sword\n");
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
		printf("Defence  : %d\t\t",heroes->armor.defence);		printf("Attack Power: %d  \t",heroes->rightHand.attackPower);	printf("Attack Power: %d\n",heroes->leftHand.attackPower);
		printf("Evasion  : %d\t\t",heroes->armor.evasion);		printf("Dexerity    : %d  \t",heroes->rightHand.dexerity);		printf("Dexerity    : %d\n",heroes->leftHand.dexerity);
		printf("HP       : %d\t\t",heroes->armor.healthPoint);	printf("Accuracy    : %d  \t",heroes->rightHand.accuracy);		printf("Accuracy    : %d\n",heroes->leftHand.accuracy);
		printf("Strength : %d\t\t",heroes->armor.strength);		printf("CRIT Power  : %d  \t",heroes->rightHand.criticalPower);	printf("CRIT Power  : %d\n",heroes->leftHand.criticalPower);
		printf("Dexerity : %d\t\t",heroes->armor.dexerity);		printf("CRIT Ratio  : %d  \t",heroes->rightHand.criticalRatio);	printf("CRIT Ratio  : %d\n",heroes->leftHand.criticalRatio);
		printf("\t\t\t");										printf("Piercing    : %d  \t",heroes->rightHand.piercingArmor);	printf("Piercing    : %d\n",heroes->leftHand.piercingArmor);
		printf("%c[33m───────────────────────────────────────────────────────────────────────%c[0m\n", 27, 27);
	}
}

void savefile(FILE *fh, CHARACTER *heroes){
	if((fh = fopen("data.txt","w")) == NULL){
		printf("ERROR: FILE OPEN\n");
		return;
	}

	int i = 0 ;
	for(i = 0; i < 5; i++){
		fprintf(fh, "%d\n", i + 1);									
		fprintf(fh, "%d\n", heroes[i].class);
		fprintf(fh, "%d\n", heroes[i].armor.defence);				
		fprintf(fh, "%d\n", heroes[i].armor.evasion);				
		fprintf(fh, "%d\n", heroes[i].armor.healthPoint);			
		fprintf(fh, "%d\n", heroes[i].armor.strength);				
		fprintf(fh, "%d\n", heroes[i].armor.dexerity);				
		fprintf(fh, "%d\n", heroes[i].rightHand.attackPower);		
		fprintf(fh, "%d\n", heroes[i].rightHand.accuracy);			
		fprintf(fh, "%d\n", heroes[i].rightHand.criticalPower);		
		fprintf(fh, "%d\n", heroes[i].rightHand.criticalRatio);		
		fprintf(fh, "%d\n", heroes[i].rightHand.piercingArmor);		
		fprintf(fh, "%d\n", heroes[i].rightHand.dexerity);			
		fprintf(fh, "%d\n", heroes[i].rightHand.strength);			
		fprintf(fh, "%d\n", heroes[i].leftHand.attackPower);		
		fprintf(fh, "%d\n", heroes[i].leftHand.accuracy);			
		fprintf(fh, "%d\n", heroes[i].leftHand.criticalPower);		
		fprintf(fh, "%d\n", heroes[i].leftHand.criticalRatio);		
		fprintf(fh, "%d\n", heroes[i].leftHand.piercingArmor);		
		fprintf(fh, "%d\n", heroes[i].leftHand.dexerity);			
		fprintf(fh, "%d\n", heroes[i].leftHand.defence);			
		fprintf(fh, "%d\n", heroes[i].leftHand.strength);			
		fprintf(fh, "%d\n", heroes[i].leftHand.rangeBlocking);		
		fprintf(fh, "%d\n", heroes[i].leftHand.meleeBlocking);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.attackPower);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.accuracy);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.criticalPower);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.criticalRatio);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.piercingArmor);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.defence);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.evasion);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.rangeBlocking);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.meleeBlocking);	
		fprintf(fh, "%d\n", heroes[i].charecterAttr.strength);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.dexerity);		
		fprintf(fh, "%d\n", heroes[i].charecterAttr.healthPoint);	
	}
	printf("File writting complete\n");
	fclose(fh);
}
	
int main (){
	CHARACTER *heroes;
	initRandom();
	FILE *fh;
	int i = 0;
	char tempC;
	char tempD;
	int classCode;

	heroes = (struct character*)malloc(sizeof(struct character) * 5);

	for(i = 0; i < 5; i++){
		showTitle();
		printf("CREATE HERO - %d\nSELECT Hero's Class or Command\n", i + 1);
		printf("[1]Knight  [2]Warrior  [3]Archer  [4]Assassin\n");
		printf("[Q]quit [A]start again [S]See all heroes\n> ");
		
		tempC = getchar();
		tempC = toupper(tempC);
		flush();
		structInit(&heroes[i]);
		
		if(tempC == 'Q') {
			i = 5;
			break;
		} else if(tempC == 'A') {
			i = -1;
			showTitle();
		} else if(tempC == 'S') {
			if(i > 0){showHero(&heroes[0]);getchar();flush();}
			if(i > 1){showHero(&heroes[1]);getchar();flush();}
			if(i > 2){showHero(&heroes[2]);getchar();flush();}
			if(i > 3){showHero(&heroes[3]);getchar();flush();}
			if(i > 4){showHero(&heroes[4]);getchar();flush();}
			i -= 1;
		} else if(tempC >= '1' && tempC <= '4'){
			classCode = atoi(&tempC);
			generator(&heroes[i], classCode);
			showHero(&heroes[i]);
			
			while(1){
				printf("Do you like this hero?\n");
				if(i == 4){
					printf("[Y] I like it. Save and Quit\n");
				} else {
					printf("[Y] I like it. Go to Next\n");
				}
				printf("[N] I Don't like it. Try again\n>");
				tempD = getchar();
				tempD = toupper(tempD);
				flush();
				
				if(tempD == 'Y' && i == 4) {
					savefile(fh, heroes);
					i = 5;
					break;
				} else if(tempD == 'Y' && i < 4) {
					break;
				} else if(tempD == 'N'){
					i -= 1;
					break;
				} else {
					printf("Wrong input. ");
				}
			}
			
		} else {
			printf("Wrong input. Please input again\n");
			i -= 1;
		}
	}
	
	free(heroes);
	
	return 0;
}






















