#include <stdio.h>

void clearScreen(){
	int i = 0;
	for(i = 0; i < 40; i++){
		printf("\n");
	}
}

void newGame(){
	printf("Not Implemented!\n");
}

void load(){
	printf("Not Implemented!\n");
}

int validate(int low, int high){
	int number = 0;
	int flag = 0;
	printf("Select: ");
	do {
		scanf("%d",&number);
		if(number < low || number > high){
			printf("Invalid input, try again: ");
		}else{
			flag = 1;
		}
	} while(flag == 0);
	return number;
}

int main(){
	int select = 0;
	clearScreen();
	while(select != 3){
		printf("--Main Menu--\n\n");
		printf("1 - New Game\n");
		printf("2 - Load Game\n");
		printf("3 - Exit\n\n");
		select = validate(1, 3);
		if(select == 1) newGame();
		else if(select == 2)load();		
		else printf("Good Bye!\n");
	}
	return 0;
}



