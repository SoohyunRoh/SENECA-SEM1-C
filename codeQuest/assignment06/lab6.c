#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

//initializing random seed
void seedRandom(){
	time_t t;
	srand((unsigned)time(&t));
}

//get random float value
float getRandom(double min, double max){
	double retVal;
	retVal = min + (((double)rand() / RAND_MAX) * (max - min));
	return retVal;
}

//get Point of status (level^2 * [min ~ max])
int getPointOfStat(int level, double min, double max){
	int retVal;
	retVal = (int)(getRandom(min, max) * level * level);
	return retVal;
}

//clean input stream buffer
void flush(){
	while(getchar() != '\n');
}

int main() {
	char cmd;
	int exitFlag = 0;
	int level = 0;
	int hp = 0;
	int strength = 0;
	int speed = 0;
	int defence = 0;
	int intelligence = 0;
	
	seedRandom();

	printf("Enemy Generator\n");
	while(cmd != '2'){
		level = (int)getRandom(3, 20);
		hp = getPointOfStat(level, 0.5, 2.0);
		strength = getPointOfStat(level, 0.15, 0.5);
		speed =    getPointOfStat(level, 0.15, 0.5);
		defence = getPointOfStat(level, 0.15, 0.5);
		intelligence = getPointOfStat(level, 0.15, 0.5);

		printf("Level\t\t- %d\n", level);
		printf("HP\t\t- %d\n", hp);
		printf("Strength\t- %d\n",strength);
		printf("Speed\t\t- %d\n",speed);
		printf("Defence\t\t- %d\n",defence);
		printf("Intelligence\t- %d\n",intelligence);

		exitFlag = 0;	//for input valid check
		printf("Generate Another ? [1]Yes, [2]No :");
		do {
			scanf("%c", &cmd);
			if(cmd != '1' && cmd != '2'){
				printf("Invalid Input. [1]Yes, [2]No :");
				exitFlag = 1;
			} else {
				exitFlag = 0;
			}
			flush();
		} while (exitFlag == 1);
	}

	return 0;
}
