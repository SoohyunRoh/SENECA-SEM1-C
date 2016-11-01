#include<stdio.h>

int main(){
	//Initialize each value
	int strength = 0;	//strength
	int speed = 0;		//speed
	int defense = 0;	//defense
	int intelligence = 0;	//intelligence
	int luck = 0;		//luck
	int sum = 0;		//value for sum
	int temp = 0;		//value for temporary

	//Intro screen (part 2)
	printf("+----------------------------+\n");
	printf("|                            |\n");
	printf("|          CODE QUEST        |\n");
	printf("|                            |\n");
	printf("+----------------------------+\n");

	//Get each status from user.	
	printf("Character Creation\n");
	printf("Please enter your desired stats for your character:\n\n");
	printf("Enter strength: ");
	scanf("%d", &strength);
	printf("Enter speed: ");
	scanf("%d", &speed );
	printf("Enter defense: ");
	scanf("%d", &defense );
	printf("Enter intelligence: ");
	scanf("%d", &intelligence );

	//Calculation luck point and total
	luck = (strength + speed + defense + intelligence) % 30;
	sum = strength + speed + defense + intelligence;

	//Calculation ratio of each points
	strength = strength * 100 / sum;
	speed = speed * 100 / sum;
	defense = defense * 100 / sum;
	intelligence = intelligence * 100 / sum;
	
	//Display result
	printf("\n\nYour player's final states are:\n\n");
	printf("Strength: %d\n", strength);
	printf("Speed: %d\n", speed);
	printf("Defense: %d\n", defense);
	printf("Intelligence: %d\n", intelligence);
	printf("Luck: %d\n", luck);

	//Initialize player's status
	/*
	int pStrength = 10;
	int pDefense = 20;
	int pIntelligence = 40;
	int pHP = 10;
	*/
	int pStrength = strength;
	int pDefense = defense;
	int pIntelligence = intelligence;
	int pHP = 10;

	//Initialize enemy's statys
	int eStrength = 30;
	int eDefense = 40;
	int eIntelligence = 25;
	int eHP = 10;

	//Decline other value
	int option = 0;
	float attackPower = 0;
	float eAttackPower = 0;

	//Battle start screen
	printf("|--------------------------------|\n");
	printf("|          Battle Start!         |\n");
	printf("|--------------------------------|\n");
	
	//Main loop : working while player and enemy alive
	while(pHP > 0 && eHP > 0){
		attackPower = 0;
		//Battle screen
		printf("--------------------------------------\n");
		printf("Your Hp %d\tEnemy HP: %d\n",pHP, eHP);
		printf("1 - Attack\n");
		printf("2 - Magic\n");
		printf("Select your move: ");

		//Input from user
		scanf("%d",&option);
		
		if(option == 1){	//Attack
			attackPower = (float)pStrength / eDefense;	
		} else if(option == 2){	//Magic
			attackPower =  (float)pIntelligence / eIntelligence;
		} else {		//Wrong input
			printf("Wrong command. Input again\n");
		}

		if(attackPower > 0.0){	//Attack or Magic (Not wrong)
			printf("You attacked the enemy!\n");
			eHP -= (int)(attackPower * 5);

			if(eHP <= 0){	//Enemy died after player's attack
				printf("You shocked the enemy!\n");
				printf("You Won!\n");
			} else {	//Enemy still alive after player's attack
				printf("The enemy attacked you!\n");
				eAttackPower = ((float)eStrength / pDefense) * 5;
				pHP -= eAttackPower;
			}

			//Enemy still alive but player died
			if(eHP > 0 && pHP <= 0){
				printf("You died!\n");
			}
		}
	}

	//Finished battle
	printf("---------End of battle---------\n");
}
