#include <stdio.h>
#include <time.h>
#include <ctype.h>

/*
	I declare that the attached assignment is wholly my own work in accordance with
	Seneca Academic Policy. No part of this assignment has been copied manually or
	electronically from any other source (including web sites) or distributed to
	other students.
	Name: Soohyun Roh			 Student ID: 057-057-143

*/

#define TESTMODE 0
//TESTMODE = 1, NORMAL = 0

//Return the tile type for index value
char getTileType(unsigned int index){
	char ret;
	ret = ' ';

	if(index % 3 == 0)ret = 'W';
	if(index % 5 == 0)ret = 'L';
	if(index % 7 == 0)ret = 'G';
	if(index == 0)ret = 'C';
	return ret;
}

//Return character for tile include player's ID
char getDisplayTile(unsigned int index, unsigned int playerPosition, char playerName){
	if(index == playerPosition)return playerName;
	return getTileType(index);
}

//Draw border repeat 'int count' times.
void drawBorder(int count, int type){
	int i;

	//Draw column repeat 'count' times
	for(i = 0; i < count; i++){
		if(type == 1)printf(" ___ ");
		else if(type == 2)printf("|___|");
		else if(type == 3)printf("     ");
	}
	if(type != 3)printf("\n");
}

//Draw border repeat 2 times with size * 2 white space
void drawMiddleBorder(int size, int type){
	int i;
	
	//Draw left top or left bottom column
	if(type == 1)printf(" ___ ");
	else if(type == 2)printf("|___|");

	//Draw middle row (white spaces)
	for(i = 0; i < size - 2; i++)printf("     ");
	
	//Draw right top or right bottom column
	if(type == 1)printf(" ___ \n");
	else if(type == 2)printf("|___|\n");
}

//Draw top or Bottom of the board
//direct: increase or decrease number of next tile(1/-1)
void drawTopOrBottomRow(unsigned int size, int ind, int direct, unsigned int playerPosition, char playerName){
	int i;
	if(ind + direct <= 0)return;

	//Draw top row
	drawBorder(size, 1);

	//Draw middle row
	for(i = 0; i < size; i++){
		printf("| %c |", getDisplayTile(ind, playerPosition, playerName));
		ind += direct;	//Increase or decrease next tile number because of spiral board
	}
	printf("\n");

	//Draw bottom row
	drawBorder(size, 2);
}

//Draw middle of the board
//size: size of side of board
//left: number of left second tile
//right: number of right second tile
void drawMiddleRow(unsigned int size, int left, int right, unsigned int playerPosition, char playerName){
	int i;
	if(left <= 1 || right <= 1)return;
	for(i = 0; i < size - 2; i++){
		//Draw left and right top column
		drawMiddleBorder(size, 1);

		//Draw left middle column
		printf("| %c |", getDisplayTile(left, playerPosition, playerName));

		//Draw middle row (white spaces)
		drawBorder(size - 2, 3);
		
		//Draw right middle column
		printf("| %c |\n", getDisplayTile(right, playerPosition, playerName));
		
		//Draw bottom row
		drawMiddleBorder(size, 2);
		
		left--;	//decrease next left tile number because of spiral board
		right++;//increase next right tile number because of spiral board
	}
}

//Draw whole board
//size: size of side of board
void displayBoard(unsigned int size, unsigned int playerPosition, char playerName){
	int maxTile = size * 4 - 5;	//get Last tile number: *Square has 4 sides
					//	* Square has 4 sides and 4 edge.
					//	  Each edge overlap next edge. 
					//	  So, we don't need overlap edge tile.
					//        And minus 1 because array start with 0.
					//        4 for 4 Edges and 1 for array.
					//        So size * 4 and takes away 5		
	drawTopOrBottomRow(size, 0, 1, playerPosition, playerName);				//draw top row
	drawMiddleRow(size, maxTile, size, playerPosition, playerName);			//draw between after top row to before bottom row
	drawTopOrBottomRow(size, maxTile - size + 2, -1, playerPosition, playerName);	//draw bottom row
}

//Forced check for tile working
int getTileTypeTest(){
	if(getTileType(153) != 'W') printf("153 should return W\n");
	else if(getTileType(65) != 'L') printf("65 should return L\n");
	else if(getTileType(49) != 'G') printf("49 should return G\n");
	else if(getTileType(0) != 'C') printf("0 should return C\n");
	else if(getTileType(105) != 'G') printf("105 should be G\n");
	else if(getTileType(79) != ' ') printf("79 should be space\n");
	else return 1;
	return 2;
}

//Clear input buffer
void flush(){
	while(getchar() != '\n');
}

//Initialize random seed
void initRandom(){
	time_t t;
	srand((unsigned)time(&t));
}

//Get random value between low and high from prompt
int getRandom(int low, int high){
	return low + (rand() % ((high + 1) - low));
}

//Get number of dice and roll it and return sum of value of dices
unsigned int playerRoll(){
	int dices, i, sum = 0, tmp = 0;
	int dicesMax = 3;
	
	printf("your turn, how many dice will you roll? ");
	
	if(TESTMODE){
		printf(" BUT THIS IS TEST MODE.\n PLAYER WILL MOVE BY YOUR INPUT\n How many tile you want to move? (1~20) ");
		dicesMax = 20;
	}
	
	dices = getValidInteger(1,dicesMax);
	
	if(!TESTMODE){
		printf("your rolled: ");
		for(i = 0; i < dices; i++){
			tmp = getRandom(1, 6);
			printf("%d ", tmp);
			sum += tmp;
		}
	} else if(TESTMODE){
		sum = dices;
	}
	printf("\n");
	
	return sum;
}

//Roll win prize
void winPrize(int playerPrizes[], unsigned int *prizeCount){
	int win;
	win = getRandom(10, 100);

	if(*prizeCount < 9){
		playerPrizes[*prizeCount] = win;
		*prizeCount = *prizeCount + 1;
		printf("you won a prize of %d\n", win);
	} else if(*prizeCount >= 10){
		printf("Inventory is full!\n");
	}
}

//Roll grand prize
void winGrandPrize(int playerPrizes[], unsigned int *prizeCount){
	int win;
	win = getRandom(100, 200);
	if(*prizeCount < 10){
		playerPrizes[*prizeCount] = win;
		*prizeCount = *prizeCount + 1;
		printf("you won a grand prize of %d \n", win);
	} else if(*prizeCount >= 10){
		printf("Inventory is full!\n");
	}
}

//Roll lose prize
int loseItem(int playerPrizes[], unsigned int *prizeCount){
	int item, i, bNum;
	bNum = (*prizeCount) - 1;	//Last array number AND decreased number of prise Counter
	
	if(*prizeCount == 0){
		printf("Player lost a one of prize in this turn but nothing to lost\n");
	} else {
		item = getRandom(0, bNum);
		printf("Player lost a prize value at %d!\n", playerPrizes[item]);

		for(i = item; i < bNum; i++){
			playerPrizes[i] = playerPrizes[i + 1];
		}
		
		playerPrizes[bNum] = 0;
		//playerPrizes[*prizeCount] = 0;	//This line has problem.
		*prizeCount = bNum;
	}
}

//Checkout and make result of the game.
int checkout(int *playerScore, int playerPrizes[], unsigned int *prizeCount){
	int sum = 0, i;
	for(i = 0; i < *prizeCount; i++){
		sum += playerPrizes[i];
		playerPrizes[i] = 0;
	}
	*prizeCount = 0;
	
	*playerScore += sum;
	printf("You checkedout for $%d.00 score is now: %d.00\n", sum, *playerScore);
	
	if(*playerScore >= 200){
		printf("You won the game!\n");
		return 1;
	} else {
		//printf("You lose the game!\n");
		return 2;
	}
}

//This function get value that between low and high from user 
int getValidInteger(int low, int high){
	int value = 0;
	scanf("%d", &value);
	while(1){
		flush();
		if(value < low || value > high){
			printf("Invalid input, try again: ");
			scanf("%d", &value);
		} else {
			break;
		}
	}
	return value;
}

//This function get character value that between low and high from user 
int getCharacterInteger(char low, char high){
	char value = 0;
	scanf("%c", &value);
	while(1){
		flush();
		if(value < low || value > high){
			printf("Invalid input, try again: ");
			scanf("%d", &value);
		} else {
			break;
		}
	}
	return value;
}

//Initialize player information.
void initPlayer(int* playerScore, int playerPrizes[], unsigned int *prizeCount, char *playerName, int *playerPosition){
	int i;

	//Initialize each value for player information
	*playerScore = 0;
	*playerPosition = 0;
	*playerName = ' ';
	//*prizeCount = 10;
	//for(i = 0; i < 10; i++) playerPrizes[i] = 100;
	*prizeCount = 0;
	for(i = 0; i < 10; i++) playerPrizes[i] = 0;

	//Get player ID from prompt
	printf("number of players is 1\n");
	printf("Enter player ID: ");
	*playerName = getCharacterInteger('!', '~'); //!:33, ~:126
}

//Show menu prompt
int menu(){
	char temp;
	int ret = 0;
	printf("Main Menu\n\n");
	printf("p-(p)lay q-(q)uit r-inst(r)uctions s-HI(s)core\n");	
	scanf("%c", &temp);
	while(ret == 0){
		flush();
		if(toupper(temp) == 'P') ret = 1;
		else if(toupper(temp) == 'Q') ret = 2;
		else if(toupper(temp) == 'R') ret = 3;
		else if(toupper(temp) == 'S') ret = 4;
		else {
			printf("Invalid input, try again: ");
			scanf("%c", &temp);
		}
	}
	return ret;
}

//This function move player and process result.
int playGame(unsigned int boardSize, int *playerScore, int playerPrizes[], unsigned int *prizeCount, char *playerName, int *playerPosition){
	int i, advancing, tmp = 0;
	int maxTile = boardSize * 4 - 5;
	char tile;
	displayBoard(boardSize, *playerPosition, *playerName);
	printf("score: %d   inventory (%d items): ", *playerScore, *prizeCount);
	for(i = 0; i < *prizeCount; i++) printf("%d, ", playerPrizes[i]);
	printf("\n");
	advancing = playerRoll();
	printf("Advancing %d spaces\n", advancing);

	*playerPosition += advancing;
	if(*playerPosition > maxTile){
		//Form of arranged numbers in board is circulation. So, when move over maxTile, it become to reduce.
		*playerPosition = *playerPosition % (maxTile + 1);	// +1 for situation of start with 0
	}

	tile = getTileType(*playerPosition);
	if(tile == 'C') {
		tmp = checkout(playerScore, playerPrizes, prizeCount);
	} else if(tile == 'W') {
		winPrize(playerPrizes, prizeCount);
	} else if(tile == 'G') {
		winGrandPrize(playerPrizes, prizeCount);
	} else if(tile == 'L') {
		loseItem(playerPrizes, prizeCount);
	} else if(tile == ' ') {
		printf("nothing happens, go again.\n");
	}
	
	return tmp;
}

int initBoard(){
	int size;
	printf("Enter board size: ");
	size = getValidInteger(5, 15);
	return size;
}

void showHiScore(int highScore, char highScorePlayer){
	printf("__         \n");
	printf("  \\_______ \n");
	printf("   \\++++++|\n");
	printf("    \\=====|\n");
	printf("     0--- 0\n\n");
	printf("HI SCORE: %d Player Name: %c\n", highScore, highScorePlayer);
}

int main(){
	int boardSize;
	int playerScore;
	int playerPosition;
	char playerName;
	int playerPrizes[10];
	int prizeCount;
	int highScore = 100;
	char highScorePlayer = ' ';
	int cmd = 0;
	int stat = 0;
	int endCondition = 0;
	initRandom();
	printf("\nWelcom to CHECKOUT\n");
	
	while(1){					//Main menu LOOP
		endCondition = 0;
		
		cmd = menu();
		if(cmd == 2){				//Quit
			break;
		} else if(cmd == 3) {		//Instructions (NOT IMPLEMENTED)
		} else if(cmd == 4) {		//HI score
			showHiScore(highScore, highScorePlayer);
		} else if(cmd == 1) {		//Play
			initPlayer(&playerScore, playerPrizes, &prizeCount, &playerName, &playerPosition);
			boardSize = initBoard();
			while(endCondition == 0){	//In game LOOP
				if(TESTMODE)printf("------------THIS IS TEST MODE------------\n");
				
				stat = playGame(boardSize, &playerScore, playerPrizes, &prizeCount, &playerName, &playerPosition);
				if(stat == 1){		//Reach to checkout tile and over threshold 
					if(playerScore >= highScore){
						highScore = playerScore;
						highScorePlayer = playerName;
					}
					endCondition = 1;
				} else if(stat == 2){	//Reach to checkout tile but under threshold
					//continue game.
				}
			}
		}
	}

	printf("This game is much more fun than bash...\n");
	return 0;

}
