#include <stdio.h>

struct Player {
	int level;
	int strength;
	int speed;
	int defense;
	int intelligence;
	int luck;
	int maxHP;
	int currentHP;
};

struct Item {
	int itemType;
	int itemPower;
};

int checkValidChar(char x){
	if(	(x <= '0' && x >= '9') ||
		(x <= 'A' && x >= 'Z') ||
		(x <= 'a' && x >= 'z') ||
		(x == '_' || x == '-') ||
		(x == '\0')) {
		return 0;
	}
	return -1;
}

void flush(){
	while(getchar() != '\n');
}

int saveGame(struct Player player, int exp, int nextLvl, float days, struct Item inventory[], int quantities[], int inventorySize){
	FILE *fp;
	char filename[51];
	int i, sget;	

	printf("Enter filename to write: ");
	sget = scanf("%50[^\n]", filename);
	flush();

	if(sget != 1)
		return 0;

	fp = fopen(filename, "w");
	if(fp != NULL){
		fprintf(fp, "%d,%d,%.1f,",exp,nextLvl,days);
		fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,",
			player.level,
			player.strength,
			player.speed,
			player.defense,
			player.intelligence,
			player.luck,
			player.maxHP,
			player.currentHP);
		for(i = 0; i < inventorySize; i++){
			fprintf(fp, "%d,%d,%d,",
				inventory[i].itemType,
				inventory[i].itemPower,
				quantities[i]);
		}
	} else {
		return 0;
	}
	fclose(fp);
	
	return 1;
}

int loadSaveGame(struct Player *player, int *exp, int *nextLvl, float *days, struct Item inventory[], int quantities[], int inventorySize){
	FILE *fp;
	char filename[51];
	int i, sget, x;	

	printf("Enter filename to read: ");
	sget = scanf("%50[^\n]", filename);
	flush();
	
	if(sget != 1) return 0;
	fp = fopen(filename, "r");
	
	if(fp != NULL){
		fscanf(fp, "%d,%d,%f,", exp, nextLvl, days);
		fscanf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,",
			&player->level,
			&player->strength,
			&player->speed,
			&player->defense,
			&player->intelligence,
			&player->luck,
			&player->maxHP,
			&player->currentHP);

		for(i = 0; i < inventorySize; i++){
			fscanf(fp, "%d,%d,%d,",
				&inventory[i].itemType,
				&inventory[i].itemPower,
				&quantities[i]);
		}
	} else {
		printf("Invalid savefile!\n");
		return 0;
	}
	fclose(fp);
	return 1;
}

int main(){
	struct Player p1;
	struct Player p2 = {0};
	struct Item i1[2];
	struct Item i2[2];
	int q1[2] = {12, 34};
	int q2[2] = {0};
	float days = 12;
	int nextLvl = 15;
	int exp = 24;
	
	p1.level = 5;
	p1.strength = 10;
	p1.speed = 30;
	p1.defense = 20;
	p1.intelligence = 40;
	p1.luck = 33;
	p1.maxHP = 50;
	p1.currentHP = 15;
	i1[0].itemType = 3;
	i1[1].itemType = 2;
	i1[0].itemPower = 40;
	i1[1].itemPower = 20;

	if(saveGame(p1, exp, nextLvl, days, i1, q1, 2) == 0){
		printf("Save file FAIL\n");
	} else {
		exp = 0;
		days = 0;
		nextLvl = 0;

		while(!loadSaveGame(&p2, &exp, &nextLvl, &days, i2, q2, 2));
		printf("       Level: %d\n", p2.level);
		printf("    Strength: %d\n", p2.strength);
		printf("       Speed: %d\n", p2.speed);
		printf("     Defense: %d\n", p2.defense);
		printf("Intelligence: %d\n", p2.intelligence);
		printf("        Luck: %d\n", p2.luck);
		printf("      Max Hp: %d\n", p2.maxHP);
		printf("  Current Hp: %d\n", p2.currentHP);
		printf(" Item-1 Type: %d\n", i2[0].itemType);
		printf("Item-1 Power: %d\n", i2[0].itemPower);
		printf("  Item-1 QTY: %d\n", q2[0]);
		printf(" Item-2 Type: %d\n", i2[1].itemType);
		printf("Item-2 Power: %d\n", i2[1].itemPower);
		printf("  Item-2 QTY: %d\n", q2[1]);
		printf("  Experience: %d\n", exp);
		printf("  Next Level: %d\n", nextLvl);
		printf("        Days: %.1f\n", days);
	}
}
