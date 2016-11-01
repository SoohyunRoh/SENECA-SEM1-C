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

typedef struct happened {
	int miss;
	int rangeBlocking;
	int meleeBlocking;
	int criticalHit;
	int piercingArmor;
	int attackType;				//0:melee, 1:range
} HAPPENED;

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
	int currentHp;
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
	printf("│                  %c[36m  Hero Arena  %c[33m                 │\n", 27, 27);
	printf("└─────────────────────────────────────────────────┘%c[0m\n", 27);
}

void structInit(CHARACTER *heroes){
	heroes->class = 0;
	heroes->currentHp = 0;
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
	
	printf("currentHp : %d\n", heroes->currentHp);
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

void loadfile(FILE *fh, CHARACTER *heroes, char *filename){
	printf("Trying open file %s ->", filename);
	if((fh = fopen(filename,"r")) == NULL){
		printf("ERROR: FILE OPEN\n");
		return;
	}
	printf("SUCCESS\n");

	int i = 0 ;
	int dummy;
	for(i = 0; i < 5; i++){
		printf("IMPORT HERO INFORMATION FROM FILE - HERO %d, Initializing:", i);
		structInit(&heroes[i]);
		printf("SUCCESS, READ FROM FILE:");
		fscanf(fh, "%d\n", &dummy);
		fscanf(fh, "%d\n", &heroes[i].class);	
		fscanf(fh, "%d\n", &heroes[i].armor.defence);				
		fscanf(fh, "%d\n", &heroes[i].armor.evasion);				
		fscanf(fh, "%d\n", &heroes[i].armor.healthPoint);			
		fscanf(fh, "%d\n", &heroes[i].armor.strength);				
		fscanf(fh, "%d\n", &heroes[i].armor.dexerity);				
		fscanf(fh, "%d\n", &heroes[i].rightHand.attackPower);		
		fscanf(fh, "%d\n", &heroes[i].rightHand.accuracy);			
		fscanf(fh, "%d\n", &heroes[i].rightHand.criticalPower);		
		fscanf(fh, "%d\n", &heroes[i].rightHand.criticalRatio);		
		fscanf(fh, "%d\n", &heroes[i].rightHand.piercingArmor);		
		fscanf(fh, "%d\n", &heroes[i].rightHand.dexerity);			
		fscanf(fh, "%d\n", &heroes[i].rightHand.strength);			
		fscanf(fh, "%d\n", &heroes[i].leftHand.attackPower);			
		fscanf(fh, "%d\n", &heroes[i].leftHand.accuracy);			
		fscanf(fh, "%d\n", &heroes[i].leftHand.criticalPower);		
		fscanf(fh, "%d\n", &heroes[i].leftHand.criticalRatio);		
		fscanf(fh, "%d\n", &heroes[i].leftHand.piercingArmor);		
		fscanf(fh, "%d\n", &heroes[i].leftHand.dexerity);			
		fscanf(fh, "%d\n", &heroes[i].leftHand.defence);				
		fscanf(fh, "%d\n", &heroes[i].leftHand.strength);			
		fscanf(fh, "%d\n", &heroes[i].leftHand.rangeBlocking);		
		fscanf(fh, "%d\n", &heroes[i].leftHand.meleeBlocking);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.attackPower);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.accuracy);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.criticalPower);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.criticalRatio);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.piercingArmor);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.defence);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.evasion);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.rangeBlocking);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.meleeBlocking);	
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.strength);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.dexerity);		
		fscanf(fh, "%d\n", &heroes[i].charecterAttr.healthPoint);
		(heroes + i)->currentHp = heroes[i].charecterAttr.healthPoint;
		
		printf("-> SUCCESS\n");
	}
	printf("File Reading complete\n");
	fclose(fh);
}

void calcFinalAttackPower(CHARACTER *heroes, double *damage, HAPPENED *happened){
	double att;
	att = (double)heroes->charecterAttr.attackPower;				//GET DEFAULT ATTACK POWER

	if(getRandom(1,1000) > heroes->charecterAttr.accuracy ) {	//Miss the target
		happened->miss = 1;
		*damage = 0;
		return;
	} 
	
	if(getRandom(1, 1000) <= heroes->charecterAttr.criticalRatio) {	//CRITICAL ATTACK
		att += ((att * heroes->charecterAttr.criticalPower) / 10);
		happened->criticalHit = 1;
	}
	
	if(getRandom(1,1000) <= heroes->charecterAttr.piercingArmor) {	//Piercing Armor
		happened->piercingArmor = 1;
	}

	*damage = att;
}

//adjust incoming attack power
void calcFinalDefence(CHARACTER *heroes, double *damage, HAPPENED *happened){
	double def = 1 - ((double)heroes->charecterAttr.defence / (CONST_DEFENCE + (double)heroes->charecterAttr.defence));		//BASIC DEFENCE FORMULA

	if(happened->attackType == 1){			//range attack
		if(getRandom(1,1000) <= heroes->charecterAttr.rangeBlocking){
			happened->rangeBlocking = 1;
			*damage = 0;
			return;
		}
	}else if(happened->attackType == 0){	//melee attack
		if(getRandom(1,1000) <= heroes->charecterAttr.meleeBlocking){
			happened->meleeBlocking = 1;
			*damage = 0;
			return;
		}
	}
	
	if(happened->piercingArmor == 1){
		return;	//no adjust incoming damage.
	}

	*damage = *damage * def;
	return;
}

void showBattle(CHARACTER *offen, CHARACTER *defen, HAPPENED *happened, double damage, int status, int turn, int round, int offenNum, int defenNum){
	printf("ROUND %c[33m%d %c[0m / turn %c[33m%d%c[0m [", 27, round, 27, 27, turn, 27);
	if(status == 0){	//RED ATTACK BLUE
		printf("%c[31mRed hero-%d%c[0m ----ATTACK---> %c[36mBlue hero-%d%c[0m]\n", 27, offenNum, 27, 27, defenNum, 27);
	} else {
		printf("%c[31mRed hero-%d%c[0m <---ATTACK---- %c[36mBlue hero-%d%c[0m]\n", 27, defenNum, 27, 27, offenNum, 27);
	}
	
	if(status == 0){
		showBar(offen->charecterAttr.healthPoint, offen->currentHp);
		printf(" %d/%d ", (int)offen->currentHp, (int)offen->charecterAttr.healthPoint);
		
		if(happened->miss == 1) printf("%c[31mATTACK MISS!%c[0m", 27, 27);
		if(happened->rangeBlocking || happened->meleeBlocking) printf("%c[31mDEFENDER BLOCKING DAMAGE%c[0m", 27, 27);
		if(happened->criticalHit == 1) printf("%c[31mCRITICAL HIT!%c[0m", 27, 27);
		if(happened->piercingArmor == 1) printf("%c[31mPIERCING ARMOR!%c[0m", 27, 27);
		
		printf(" ----[%d]--->", (int)damage);
	} else {
		showBar(defen->charecterAttr.healthPoint, defen->currentHp);
		printf(" %d/%d", (int)defen->currentHp, (int)defen->charecterAttr.healthPoint);
		printf(" <---[%d]---- ", (int)damage);
		
		if(happened->miss == 1) printf("%c[31mATTACK MISS!%c[0m", 27, 27);
		if(happened->rangeBlocking || happened->meleeBlocking) printf("%c[31mDEFENDER BLOCKING DAMAGE%c[0m", 27, 27);
		if(happened->criticalHit == 1) printf("%c[31mCRITICAL HIT!%c[0m", 27, 27);
		if(happened->piercingArmor == 1) printf("%c[31mPIERCING ARMOR!%c[0m", 27, 27);
	}

	if(status == 0){
		showBar(defen->charecterAttr.healthPoint, defen->currentHp);
		printf(" %d/%d\n", (int)defen->currentHp, (int)defen->charecterAttr.healthPoint);
	} else {
		showBar(offen->charecterAttr.healthPoint, offen->currentHp);
		printf(" %d/%d\n", (int)offen->currentHp, (int)offen->charecterAttr.healthPoint);
	}
}

int main(){
	CHARACTER *redTeam;
	CHARACTER *blueTeam;
	CHARACTER *offen;
	CHARACTER *defen;
	char redTeamFile[50];
	char blueTeamFile[50];
	FILE *fh1;
	FILE *fh2;
	
	redTeam = (struct character*)malloc(sizeof(struct character) * 5);
	blueTeam = (struct character*)malloc(sizeof(struct character) * 5);
	initRandom();
	
	system("clear");
	system("ls -l");
	printf("Input name of data file for RED TEAM : ");
	scanf("%s", &redTeamFile);
	flush();
	printf("Input name of data file for BLUE TEAM : ");
	scanf("%s", &blueTeamFile);
	flush();
	
	loadfile(fh1, redTeam, redTeamFile);
	loadfile(fh2, blueTeam, blueTeamFile);
	
	showTitle();
	printf("Let's fight Red team 5 heroes and Blue team 5 heroes.\n");
	
	int status;
	int turn = 0;
	int round = 1;
	int redNum = 0;
	int blueNum = 0;
	int offenNum = 0;
	int defenNum = 0;
	
	
	if(getRandom(1,2) == 1){
		printf("First attacker is %c[31mRed team hero-1%c[0m and %c[36mBlue team hero-1%c[0m takes 115%% defence at first round.\n", 27, 27, 27, 27);
		status = 0;
		
		offen = &redTeam[redNum];
		defen = &blueTeam[blueNum];
	} else {
		printf("First attacker is %c[36mBlue team hero-1%c[0m and %c[31mRed team hero-1%c[0m takes 115%% defence at first round.\n", 27, 27, 27, 27);
		status = 1;
		
		offen = &blueTeam[blueNum];
		defen = &redTeam[redNum];
	}

	defen->charecterAttr.defence = defen->charecterAttr.defence * 1.15;
	
	printf("\n\n==============  Round 1  ==============\n");
	printf("%c[31mRed team hero-1%c[0m\n", 27, 27);
	showHero(&redTeam[redNum]);
	printf("\n%c[36mBlue team hero-1%c[0m\n", 27, 27);
	showHero(&blueTeam[blueNum]);
		
	while(redNum < 5 && blueNum < 5){
		
		double damage = 0;
		HAPPENED happened = {0};
		
		if(status == 0){
			offenNum = redNum + 1;
			defenNum = blueNum + 1;
			
			offen = &redTeam[redNum];
			defen = &blueTeam[blueNum];
		} else {
			offenNum = blueNum + 1;
			defenNum = redNum + 1;
			
			offen = &blueTeam[blueNum];
			defen = &redTeam[redNum];
		}

		if(offen->class == ARCHER)happened.attackType == 1;
		
		calcFinalAttackPower(offen, &damage, &happened);
		calcFinalDefence(defen, &damage, &happened);
		defen->currentHp -= damage;
		turn++;
		
		showBattle(offen, defen, &happened, damage, status, turn, round, offenNum, defenNum);

		if(defen->currentHp <= 0){	//defender die
			if(status == 0){	//attacker was red, blue hero die
				blueNum++;
				printf("\n===========%c[31mRed team hero-%d %c[0mWIN===========\n\n", 27, redNum+1, 27);
			} else {			//attacker was blue, red hero die
				redNum++;
				printf("\n===========%c[36mBlue team hero-%d %c[0mWIN===========\n\n", 27, blueNum+1, 27);
			}
			round++;
			turn = 0;
			
			if(redNum < 5 && blueNum < 5){
				printf("\n\n==============  Round %d  ==============\n", round);
				printf("%c[31mRed team hero-%d%c[0m\n", 27, redNum + 1, 27);
				showHero(&redTeam[redNum]);
				printf("\n%c[36mBlue team hero-%d%c[0m\n", 27, blueNum + 1, 27);
				showHero(&blueTeam[blueNum]);
			}
		}

		if(status == 0){	//change blue and red
			status = 1;
		} else {
			status = 0;
		}

		getchar();
		flush();
	}
	
	if(status == 0){	//change blue and red
		printf("\n****************%c[36mBlue team WIN%c[0m WIN****************\n\n", 27, 27);
	} else {
		printf("\n****************%c[31mRed team WIN%c[0m WIN****************\n\n", 27, 27);
	}
	
}











