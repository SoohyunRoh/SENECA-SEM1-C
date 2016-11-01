#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

/*
	I declare that the attached assignment is wholly my own work in accordance with
	Seneca Academic Policy. No part of this assignment has been copied manually or
	electronically from any other source (including web sites) or distributed to
	other students.
	Name: Soohyun Roh			 Student ID: 057-057-143

*/

#define MAX_INVENTORY_SIZE 10
#define MAX_PLAYER 8
#define MIN_DICES 1
#define MAX_DICES 3
#define MAX_DICE_SIDE 6
#define MIN_WIN_PRIZE 10
#define MAX_WIN_PRIZE 100
#define MIN_GRAND_WIN_PRIZE 100
#define MAX_GRAND_WIN_PRIZE 200
#define WIN_SCORE 200
#define MAX_LENGTH_PLAYERNAME 35

//Struct for a player
struct Player {
	int playerScore;
	int playerPosition;
	char playerID;
	char playerName[MAX_LENGTH_PLAYERNAME + 1];
	int prizeCount;
	int playerPrizes[MAX_INVENTORY_SIZE];
};

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

//This function get value that between low and high from user 
unsigned int getValidInteger(int low, int high){
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
	flush();
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

//GetTileType from given index number. It can check multi playerID.
char getTileType(unsigned int index, struct Player players[], unsigned int playerCount, int type) {
	char ret;
	int i = 0;
	ret = ' ';
	if(type == 0){
		for(i = 0; i < playerCount; i++){	//Check each players position that match with index
			if(index == players[i].playerPosition){
				return players[i].playerID;
			}
		}
	}
	if(index % 3 == 0)ret = 'W';
	if(index % 5 == 0)ret = 'L';
	if(index % 7 == 0)ret = 'G';			//Concider to COMMON DIVISOR (G.C.D)
	if(index == 0)ret = 'C';
	return ret;
}

//Draw border repeat 'int count' times.
void drawBorder(int count, int type){
	int i;

	for(i = 0; i < count; i++){			//Draw column repeat 'Count' times
		if(type == 1)printf(" ___ ");
		else if(type == 2)printf("|___|");
		else if(type == 3)printf("     ");
	}
	if(type != 3)printf("\n");
}

//Draw border repeat 2 times with size * 2 white space
void drawMiddleBorder(int size, int type){
	int i;
	if(type == 1)printf(" ___ ");			//Draw top of left or bottom of left column
	else if(type == 2)printf("|___|");
	
	for(i = 0; i < size - 2; i++)printf("     ");	//Draw middle row (white space)
	
	if(type == 1)printf(" ___ \n");			//Draw top of right or bottom of right column
	else if(type == 2)printf("|___|\n");
}

//Draw top or Bottom of the board
void drawTopOrBottomRow(unsigned int size, int index, int direct, struct Player players[], unsigned int playerCount){
	int i;
	if(index + direct <= 0)return;	//Do not allow backwardness
	drawBorder(size, 1);		//Draw top row
	for(i = 0; i < size; i++){	//Draw middle row
		printf("| %c |", getTileType(index, players, playerCount, 0));
		index += direct;	//Increase or decrease next tile number because of spiral board
	}
	printf("\n");
	drawBorder(size, 2);		//Draw bottom row
}

//Draw middle of the board
void drawMiddleRow(unsigned int size, int left, int right, struct Player players[], unsigned int playerCount){
	int i;
	if(left <= 1 || right <= 1)return;
	for(i = 0; i < size - 2; i++){
		drawMiddleBorder(size, 1);						//Draw left and right top column
		printf("| %c |", getTileType(left, players, playerCount, 0));		//Draw left middle column
		drawBorder(size - 2, 3);						//Draw middle row (white spaces)
		printf("| %c |\n", getTileType(right, players, playerCount, 0));	//Draw right middle column
		drawMiddleBorder(size, 2);						//Draw bottom row
		left--;		//decrease next left tile number because of spiral board
		right++;	//increase next right tile number because of spiral board
	}
}

//Draw whole board
void displayBoard(unsigned int size, struct Player players[], unsigned int playerCount){
	int maxTile = size * 4 - 5;	//get Last tile number: *Square has 4 sides
	drawTopOrBottomRow(size, 0, 1, players, playerCount);			//draw top row
	drawMiddleRow(size, maxTile, size, players, playerCount);		//draw between after top row to before bottom row
	drawTopOrBottomRow(size, maxTile - size + 2, -1, players, playerCount);	//draw bottom row
}

//Get number of dice and roll it and return sum of value of dices
unsigned int playerRoll(struct Player *player){
	int dices, i, sum = 0, tmp = 0;

	printf("%s's (%c) turn, how many dice will you roll? ", (*player).playerName, (*player).playerID);
	dices = getValidInteger(MIN_DICES,MAX_DICES);
	
	printf("your rolled: ");
	for(i = 0; i < dices; i++){		//Repeat by number of dices
		tmp = getRandom(1, MAX_DICE_SIDE);		//Dice has MAX_DICE_SIDE sides
		printf("%d ", tmp);
		sum += tmp;
	}
	printf("\n");
	return sum;
}

//Roll win prize
void winPrize(struct Player *player){
	int win;
	win = getRandom(MIN_WIN_PRIZE, MAX_WIN_PRIZE);

	if((*player).prizeCount < MAX_INVENTORY_SIZE){		//Player has enought space of inventory
		(*player).playerPrizes[(*player).prizeCount] = win;	//Put prize to last space of inventory
		(*player).prizeCount = (*player).prizeCount + 1;	//Increase 1 for prize count
		printf("you won a prize valued at %d\n", win);
	} else if((*player).prizeCount >= MAX_INVENTORY_SIZE){	//Not enought space of inventory
		printf("Inventory is full!\n");
	}
}

//Roll win grand prize
//This function is almost same with winPrise() but minimun value of roll is different with that.
void winGrandPrize(struct Player *player){
	int win;
	win = getRandom(MIN_GRAND_WIN_PRIZE, MAX_GRAND_WIN_PRIZE);

	if((*player).prizeCount < MAX_INVENTORY_SIZE){
		(*player).playerPrizes[(*player).prizeCount] = win;
		(*player).prizeCount = (*player).prizeCount + 1;
		printf("you won a prize valued at %d\n", win);
	} else if((*player).prizeCount >= MAX_INVENTORY_SIZE){
		printf("Inventory is full!\n");
	}
}

//Roll lose prize
int loseItem(struct Player *player){
	int item, i, bNum, retVal;
	bNum = (*player).prizeCount - 1;	//Last array number AND decreased number of prise Counter
	
	if((*player).prizeCount <= 0){		//Player has no prize for lose
		printf("Player lost a one of prize in this turn but nothing to lost\n");
	} else {				//Player has prize over 1
		item = getRandom(0, bNum);	//get array number to lose
		printf("Player lost a prize value at %d!\n", (*player).playerPrizes[item]);
		for(i = item; i < bNum; i++){	//Push prizes ,located after lose prize, to forward 1 step.
			(*player).playerPrizes[i] = (*player).playerPrizes[i + 1];
		}
		
		(*player).playerPrizes[bNum] = 0;
		(*player).prizeCount = bNum;	//Decrease 1
	}
}

//Checkout and make result of the game.
int checkout(struct Player *player){
	int sum = 0, i;
	for(i = 0; i < (*player).prizeCount; i++){
		sum = sum + (*player).playerPrizes[i];	//Get sum of inventory
		(*player).playerPrizes[i] = 0;		//Initialize inventory
	}
	(*player).prizeCount = 0;			//set 0 to prizeCount
	(*player).playerScore = (*player).playerScore + sum;	//Add sum to player's score
	printf("__         \n");
	printf("  \\_______ \n");
	printf("   \\++++++|\n");
	printf("    \\=====|\n");
	printf("     0--- 0\n\n");
	printf("%s (%c) checkedout for $%d\n", (*player).playerName, (*player).playerID, (*player).playerScore);
	
	if((*player).playerScore >= WIN_SCORE){
		return 1;				//Finish the game
	} else {
		return 2;				//Continue the game
	}
}

//get board size
unsigned int initBoard(){
	unsigned int size;
	printf("Enter board size: ");
	size = getValidInteger(5, 15);			//Get board size
	return size;
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
		if(toupper(temp) == 'P') ret = 1;	//Play
		else if(toupper(temp) == 'Q') ret = 2;	//Quit
		else if(toupper(temp) == 'R') ret = 3;	//Instructions
		else if(toupper(temp) == 'S') ret = 4;	//HI score
		else {
			printf("Invalid input, try again: ");
			scanf("%c", &temp);
		}
	}
	return ret;
}

void initPlayer(struct Player *player){
	int i;
	//Initialize each value for player information
	(*player).playerScore = 0;
	(*player).playerPosition = 0;
	(*player).playerID = ' ';
	strcpy((*player).playerName, "");		//STRING INITIALIZE
	(*player).prizeCount = 0;
	for(i = 0; i < MAX_INVENTORY_SIZE; i++) (*player).playerPrizes[i] = 0;
}

void getValidString(char name[]){
	scanf("%35[^\n]", name);
	while(strlen(name) == 0){
		printf("Invalid input, try again: ");
		scanf("%35[^\n]", name);
	}
}

//Prompt player ID
void getPlayerId(struct Player players[], unsigned int *playerCount){
	int i;
	printf("Enter number of players: ");
	*playerCount = getValidInteger(1,MAX_PLAYER);	//Get number of player
	for(i = 0; i < *playerCount; i++){
		printf("Enter player name: ");
		getValidString(players[i].playerName);
		
		printf("Enter player ID: ");				//Get player name of each players
		players[i].playerID = getCharacterInteger('!', '~');	//!:33, ~:126
	}
}

//Player A steal item from Player B
void stealItem(struct Player *playerA, struct Player *playerB){
	int bNum, item, i;
	
	if((*playerB).prizeCount == 0){			//unable to steal item from PLAYER B
		printf("You were unable to steal from %c.\n", (*playerB).playerID);
	} else {		
		bNum = (*playerB).prizeCount - 1;	//Last array number AND decreased number of prise Counter
		item = getRandom(0, bNum);
		
		if((*playerA).prizeCount < MAX_INVENTORY_SIZE){		//prize count under MAX_INVENTORY_SIZE
			(*playerA).playerPrizes[(*playerA).prizeCount] = (*playerB).playerPrizes[item];	//Steal
			(*playerA).prizeCount = (*playerA).prizeCount + 1;	//Increase PLAYER A's prizeCount 
			printf("You stole a prize from %c.\n", (*playerB).playerID);
		} else {							//prize count above MAX_INVENTORY_SIZE
			printf("You tried to steal item from %c, but your inventory was full.\n", (*playerB).playerID);
		}
		
		for(i = item; i < bNum; i++){		//Stolen OR lost PLAYER B's prize
			(*playerB).playerPrizes[i] = (*playerB).playerPrizes[i + 1];
		}
		
		(*playerB).playerPrizes[bNum] = 0;
		(*playerB).prizeCount = bNum;		//Decrease PLAYER B's prizeCount 
	}
}

//Find who occuipe the tileNum
int findOccpPlayer(unsigned int tileNum, struct Player players[], unsigned int playerCount, unsigned int movingPlayer){
	int i;
	for(i = 0; i < playerCount; i++){	//Ignore movingPlayer and check all players position.
		if(i != movingPlayer && players[i].playerPosition == tileNum)return i;
	}
	return -1;	//Empty tile.
}

void playGame(unsigned int boardSize, struct Player players[], unsigned int playerCount){
	int i, j, chk;
	int advancing;
	int maxTile = boardSize * 4 - 5;
	char tile;
	int who = -1;
	int firstPosition;

	for(i = 0; i < playerCount; i++){					//rotate each player
		/* For debug 
		printf("------------ALL PLAYER'S STATUS------------\n");
		int k, l;
		for(k = 0; k < playerCount; k++){
			printf("   PLAYER ID : %c (POS:%d)\n", players[k].playerID, players[k].playerPosition);
			printf("PLAYER PRIZE : ");
			for(l = 0; l < players[k].prizeCount; l++)printf("%d,",players[k].playerPrizes[l]);
			printf("\n\n");
		}	*/
		displayBoard(boardSize, players, playerCount);		//draw board
		advancing = playerRoll(&players[i]);			//roll dice and get number of tile to go
		firstPosition = players[i].playerPosition;		//For compair with backwarded location
		players[i].playerPosition = moveFoward(players[i].playerPosition, advancing, maxTile);		//Move to new tile
		
		do {
			who = findOccpPlayer(players[i].playerPosition, players, playerCount, i);
			if(who > -1){	
				stealItem(&players[i], &players[who]);						//try to steal Item
				players[i].playerPosition = moveBackward(players[i].playerPosition, maxTile);	//moves back one tile.
			}
		} while (who != -1);
			//Finishe all moves back tile, Respond to tile Player A land on.
			tile = getTileType(players[i].playerPosition, players, playerCount, 1);	//1:Tile type without player's ID
			if(firstPosition != players[i].playerPosition){
				if(tile == 'C') {			//Check out
					chk = checkout(&players[i]);
				} else if(tile == 'W') {		//Win prize
					winPrize(&players[i]);
				} else if(tile == 'G') {		//Grand prize
					winGrandPrize(&players[i]);
				} else if(tile == 'L') {		//Lose prize
					loseItem(&players[i]);
				} else if(tile == ' ') {		//Nothing to do
					printf("You do nothing.\n");
				}
			}
			if(chk == 1)break;	//PLAYER CHECK OUT AND WIN THE GAME.

	}
}

//Move player's position to forward 'advancing' tiles
int moveFoward(int position, int advancing, int maxTile){
	position = position + advancing;
	if(position > maxTile){				//Out of range
		//Form of arranged numbers in board is circulation. So, when move over maxTile, it become to reduce.
		position = position % (maxTile + 1);	// +1 for situation of array start with 0 
	}
	return position;
}

//Move player's position to back 1 tile.
int moveBackward(int position, int maxTile){
	position = position - 1;
	if(position < 0){
		position = maxTile;
	}
	return position;
}

//Find who reached to checkout and check it is endcondition
int getCheckoutPlayer(struct Player players[], unsigned int playerCount){
	int i;
	for(i = 0; i < playerCount; i++){
		if(players[i].playerScore >= WIN_SCORE) return i;
	}
	return -1;
}

void displayInstructions(){
	int maxPlayer = MAX_PLAYER;
	int winScore = WIN_SCORE;
	int minDices = MIN_DICES;
	int maxDices = MAX_DICES;
	printf("*********************\n");
	printf("*  Full Game Rules  *\n");
	printf("*********************\n");
	printf("Up to %d players compete to be the first to obtain $%d\n", maxPlayer, winScore);
	printf("Game takes place on a square board with 5 tile types\n");
	printf("->Empty Tile: No effect\n");
	printf("->Win Tile (W): Win a ramdon prize\n");
	printf("->Lose Tile (L): Lose a random prize\n");
	printf("->Grand Prize Tile (G): Win a grand prize\n");
	printf("->Checkout Tile (C): Sells all your prizes for cash\n\n");
	printf("Player can roll %d - %d dice to determine how many tiles they move each turn\n", minDices, maxDices);
	printf("If a player lands on the same tile as another player, that player steals a prize and move 1 tile back\n\n");
}


void addToLeaderboard(int game, struct Player *winner){
	FILE *fp;
	fp = fopen("Leaderboard.dat", "a");	//Open save file for append
	if(fp != NULL){
		//playerName must not contain character '('
		fprintf(fp, "GAME:%d %s(%c)-%d\n", game, (*winner).playerName, (*winner).playerID, (*winner).playerScore);
		printf("The winner's score is saved to a file Leaderboard.dat\n\n");
	} else {
		printf("ERROR: FILE SAVE - FAIL\n");
	}
	fclose(fp);
}

void displayHigherScore(){
	FILE *fp;
	int game;
	char playerName[35];
	char playerID;
	int score = 0;
	
	char tempName[35];
	char strScore[5];
	char tempID;
	int tempScore;
	
	fp = fopen("Leaderboard.dat", "r");	//Open save file for read
	if(fp != NULL){
		while(!feof(fp)){			//Scan file until reach to end of file
			fscanf(fp, "GAME:%d %[^(](%c)-%d\n", &game, tempName, &tempID, &tempScore);
			if(tempScore >= score){	//update higest record
				strcpy(playerName, tempName);
				playerID = tempID;
				score = tempScore;
			}
		}
		fclose(fp);
	} else {
		printf("No data available!\n\n");
	}

	if(score > 0){
		sprintf(strScore, "$%d\0",score);	//Integer value 'score' convert to string and append '$' to front
		printf("********************************************\n");
		printf("        Player With the Highest Score       \n");
		printf("********************************************\n");
		printf("Player Name                        ID  Score\n\n");
		printf("%-35s(%c) %5s\n", playerName, playerID, strScore);	//-35s : Left align with 35 space.
	}

}

int main(){
	struct Player players[MAX_PLAYER];
	unsigned int playerCount = 0;
	unsigned int cmd = 0;		//command code from main menu prompt
	unsigned int boardSize;
	int i, winner, game = 0;

	initRandom();
	printf("\nWelcom to CHECKOUT\n");
	
	while(1){
		cmd = menu();
		if(cmd == 2){			//Quit
			break;
		} else if(cmd == 3) {
			displayInstructions();
		} else if(cmd == 4) {		//HI score
			displayHigherScore();
		} else if(cmd == 1) {		//Play
			game++;
			for(i = 0; i < MAX_PLAYER; i++) initPlayer(&players[i]);
			getPlayerId(players, &playerCount);	//get number of player and id of each player from prompt
			boardSize = initBoard();		//get board size from prompt
			winner = -1;				//No winner. (Game start and playing condition)
			
			while(winner == -1){			//In game LOOP
				playGame(boardSize, players, playerCount);
				winner = getCheckoutPlayer(players, playerCount);	//Check game end condition
			}

			//Someone won
			printf("\nCongratulations %s (%c)! You win!\n\n", players[winner].playerName, players[winner].playerID);
			addToLeaderboard(game, &players[winner]);
		}
	}
	
	printf("This game is much more fun than bash...\n");
	return 0;
}
