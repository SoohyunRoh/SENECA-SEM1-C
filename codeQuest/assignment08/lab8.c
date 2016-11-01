#include <stdio.h>

struct player {
	int level;
	int strength;
	int speed;
	int defense;
	int intelligence;
	int luck;
	int maxHP;
	int currentHP;
};

struct item {
	int itemType;
	int itemPower;
};

//Get player information from prompt
struct player loadPlayer(){
	struct player ret;
	printf("\nPlease enter the following player info:\n");
	printf("Level: ");
	ret.level = getValidInput(1, 100);
	printf("Strength: ");
	ret.strength = getValidInput(1, 999);
	printf("Speed: ");
	ret.speed = getValidInput(1, 999);
	printf("Defense: ");
	ret.defense = getValidInput(1, 999);
	printf("Intelligence: ");
	ret.intelligence = getValidInput(1, 999);
	printf("Luck: ");
	ret.luck = getValidInput(1, 999);
	printf("Max HP: ");
	ret.maxHP = getValidInput(1, 99999);
	ret.currentHP = ret.maxHP;	
	return ret;
}

//Get item information from prompt
struct item loadItem(){
	struct item ret;
	printf("\nPlease enter the following item info:\n");
	printf("Type: ");
	ret.itemType = getValidInput(1, 100);
	printf("Power: ");
	ret.itemPower = getValidInput(1, 999);
	return ret;
}


void printData(struct player p1, struct item itemList[], int size){
	int i;
	printf("\nCollected Input: \n\n");
	printf("Lvl\tStr\tSpd\tDef\tInt\tLck\tMHP\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n\n", p1.level, p1.strength, p1.speed, p1.defense, p1.intelligence, p1.luck, p1.maxHP);
	printf("Type\tPower\n");
	for(i = 0; i < size; i++){
		printf("%d\t%d\n", itemList[i].itemType, itemList[i].itemPower);
	}
	
}

void flush(){
	while(getchar() != '\n');
}

int getValidInput(int low, int high){
	int in;
	while(1){
		scanf("%d", &in);
		flush();
		if(in < low || in > high){
			printf("Invalid input. Try again: ");
		}else{
			return in;
		}
	}
	return -1;
}

int main(){
	struct player p1;
	struct item itemList[2];
	
	p1 = loadPlayer();			//get player information from prompt
	itemList[0] = loadItem();	//get item 1 information from prompt
	itemList[1] = loadItem();	//get item 2 information from prompt
	
	printData(p1, itemList, 2);	//print player and items data
	
	return 0;
}
