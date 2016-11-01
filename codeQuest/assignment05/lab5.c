#include <stdio.h>

//Function Prototypes
void rest_at_inn(float *days_remaning, int *hp_remaning, int max);
void train(float *days_remaning, int *hp_remaning, int *experience);
void battle_demon_lord(int * current_hp);

//Main function
int main(){

	int select;

	//Initialize Real values
	float days = 8.0;
	int hp = 10;
	int maxHp = 10;
	int experience = 0;
	
	//Initialize Pointer values
	float *pDays = &days;
	int *pHp = &hp;
	int *pExperience = &experience;
	
	//Main loop
	while(1){
		printf("\nDays remaning: %.1lf\tHP: %d\tEXP: %d\n\n",days, hp, experience);
		printf(" 1 - Rest at Inn\n");
		printf(" 2 - Train\n");
		printf(" 3 - Fight the Demon Lord\n");
		printf(" 4 - Quit Game\n\n");
		printf(" Select: ");
		scanf("%d", &select);

		if(select == 1){		//REST AT INN
			rest_at_inn(pDays, pHp, maxHp);

		} else if(select == 2){		//TRAIN
			train(pDays, pHp, pExperience);

		} else if(select == 3){		//FIGHT THE DEMON LORD
			battle_demon_lord(pHp);

		} else if(select == 4){		//QUIT GAME
			printf("Quit game");
			break;
		} else {			//SELECTED WRONG NUMBER
			printf("It's wrong selece. Try again.\n");
			continue;
		}

		if(days <= 0.0 || hp <= 0){	//Game over condition;
			printf("Game Over!\n");
			break;
		}	
	}

	return 0;
}

//Recover Hp 
void rest_at_inn(float *days_remaning, int *hp_remaning, int max){
	*days_remaning -= 1;
	*hp_remaning = max;
	printf("You rested up at the inn\n");
}

//Increase Exp
void train(float *days_remaning, int *hp_remaning, int *experience){
	*days_remaning -= 0.5;
	*hp_remaning -= 2;
	*experience += 10;
	printf("You did some traning!\n");
}

//Battle
void battle_demon_lord(int *current_hp){
	*current_hp = 0;
	printf("He's too strong!\n");
}



