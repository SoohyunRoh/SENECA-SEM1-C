#include <stdio.h>

//Return the tile type for index value
//param : int - index value
//return char: tile type
//		C: Checkout, W: Win prize, L: Lose prize, G: Grand prize
char getTileType(unsigned int index){
	char ret;
	ret = ' ';

	if(index % 3 == 0)ret = 'W';
	if(index % 5 == 0)ret = 'L';
	if(index % 7 == 0)ret = 'G';
	if(index == 0)ret = 'C';
	return ret;
}

//Draw border repeat 'int count' times.
//Call this function when drawing top and bottom part on the board
//type: 1. top, 2:bottom. 3:white space 
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
//Call this function when drawing middle part on the board
//type: 1. top, 2:bottom
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
//size: size of one side of board
//ind: number of start tile
//direct: increase or decrease number of next tile(1/-1)
void drawTopOrBottomRow(unsigned int size, int ind, int direct){
	int i;
	if(ind + direct <= 0)return;

	//Draw top row
	drawBorder(size, 1);

	//Draw middle row
	for(i = 0; i < size; i++){
		printf("| %c |", getTileType(ind));
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
void drawMiddleRow(unsigned int size, int left, int right){
	int i;
	if(left <= 1 || right <= 1)return;
	for(i = 0; i < size - 2; i++){
		//Draw left and right top column
		drawMiddleBorder(size, 1);

		//Draw left middle column
		printf("| %c |", getTileType(left));

		//Draw middle row (white spaces)
		drawBorder(size - 2, 3);
		
		//Draw right middle column
		printf("| %c |\n", getTileType(right));
		
		//Draw bottom row
		drawMiddleBorder(size, 2);
		
		left--;	//decrease next left tile number because of spiral board
		right++;//increase next right tile number because of spiral board
	}
}

//Draw whole board
//size: size of side of board
void displayBoard(unsigned int size){
	int maxTile = size * 4 - 5;	//get Last tile number: *Square has 4 sides
					//	* Square has 4 sides and 4 edge.
					//	  Each edge overlap next edge. 
					//	  So, we don't need overlap edge tile.
					//        And minus 1 because array start with 0.
					//        4 for 4 Edges and 1 for array.
					//        So size * 4 and takes away 5		

	drawTopOrBottomRow(size, 0, 1);				//draw top row
	drawMiddleRow(size, maxTile, size);			//draw between after top row to before bottom row
	drawTopOrBottomRow(size, maxTile - size + 2, -1);	//draw bottom row
}

//Clear input buffer
void flush(){
	while(getchar() != '\n');
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

int main(){
	int size;

	printf("\n--Program Start--\n\n");
	if(getTileTypeTest() == 1){
		printf("getTileType test passed!\n");
		printf("Enter board size: ");
		scanf("%d", &size);
		flush();
					
		displayBoard(size);	//draw board by request
		printf("\n--Program End--\n\n");
	}
	return 0;
}
