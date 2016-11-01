#include <stdio.h>

int main() {
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

	return 0;
}
