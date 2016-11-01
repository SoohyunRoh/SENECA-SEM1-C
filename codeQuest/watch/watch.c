#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void convertEightDigit(unsigned short int num, char digit[]){
	/*
	 	 ##0##
		#     #
		5     1
		#     #
		 ##6##
		#     #
		4     2
		#     #
		 ##3##
	*/
	int i = 0;
	for(i = 0; i < 7; i++)digit[i] = 0;

	if(num == 1){
		digit[1] = 1;
		digit[2] = 1;
	}
	if(num == 2){
		digit[0] = 1;
		digit[1] = 1;
		digit[6] = 1;
		digit[4] = 1;
		digit[3] = 1;
	}
	if(num == 3){
		digit[0] = 1;
		digit[1] = 1;
		digit[6] = 1;
		digit[2] = 1;
		digit[3] = 1;
	}
	if(num == 4){
		digit[5] = 1;
		digit[6] = 1;
		digit[1] = 1;
		digit[2] = 1;
	}
	if(num == 5){
		digit[0] = 1;
		digit[5] = 1;
		digit[6] = 1;
		digit[2] = 1;
		digit[3] = 1;
	}
	if(num == 6){
		digit[0] = 1;
		digit[5] = 1;
		digit[4] = 1;
		digit[3] = 1;
		digit[2] = 1;
		digit[6] = 1;
	}
	if(num == 7){
		digit[5] = 1;
		digit[0] = 1;
		digit[1] = 1;
		digit[2] = 1;
	}
	if(num == 8){
		digit[0] = 1;
		digit[1] = 1;
		digit[2] = 1;
		digit[3] = 1;
		digit[4] = 1;
		digit[5] = 1;
		digit[6] = 1;
	}
	if(num == 9){
		digit[0] = 1;
		digit[1] = 1;
		digit[2] = 1;
		digit[3] = 1;
		digit[5] = 1;
		digit[6] = 1;
	}
	if(num == 0){
		digit[0] = 1;
		digit[1] = 1;
		digit[2] = 1;
		digit[3] = 1;
		digit[4] = 1;
		digit[5] = 1;
	}
}

void convertFNC(char fnc[][9], char digit[]){
	int i, j;
	
	for(i = 0; i < 7; i++)
		for(j = 0; j < 9; j++)
			fnc[i][j] = ' ';
	
	if(digit[0] == 1){
		fnc[1][0] = '#';	fnc[2][0] = '#';	fnc[3][0] = '#';	fnc[4][0] = '#';	fnc[5][0] = '#';
	}
	if(digit[1] == 1){
		fnc[6][1] = '#';	fnc[6][2] = '#';	fnc[6][3] = '#';
	}
	if(digit[2] == 1){
		fnc[6][5] = '#';	fnc[6][6] = '#';	fnc[6][7] = '#';
	}
	if(digit[3] == 1){
		fnc[1][8] = '#';	fnc[2][8] = '#';	fnc[3][8] = '#';	fnc[4][8] = '#';	fnc[5][8] = '#';
	}
	if(digit[4] == 1){
		fnc[0][5] = '#';	fnc[0][6] = '#';	fnc[0][7] = '#';
	}
	if(digit[5] == 1){
		fnc[0][1] = '#';	fnc[0][2] = '#';	fnc[0][3] = '#';
	}
	if(digit[6] == 1){
		fnc[1][4] = '#';	fnc[2][4] = '#';	fnc[3][4] = '#';	fnc[4][4] = '#';	fnc[5][4] = '#';
	}
}

/*				  1 		2		  3			4		  5   ->i
		0123456789012345678901234567890123456789012345678901234
	 0   ##0##    ##0##     ##0##    ##0##     ##0##    ##0## 
	 1	#     #  #     #   #     #  #     #   #     #  #     #
	 2	5  1  1  5  2  1 # 5  3  1  5  4  1 # 5  5  1  5  6  1
	 3	#     #  #     #   #     #  #     #   #     #  #     #
	 4	 ##6##    ##6##     ##6##    ##6##     ##6##    ##6## 
	 5	#     #  #     #   #     #  #     #   #     #  #     #
	 6	4     2  4     2 # 4     2  4     2 # 4     2  4     2
	 7	#     #  #     #   #     #  #     #   #     #  #     #
	 8	 ##3##    ##3##     ##3##    ##3##     ##3##    ##3## 
	*/
void copyFNCtoBOARD(char board[][9], char fnc[][9], int radix){
	int i, j, start;
	switch(radix) {
		case 0:
			start = 0;
			break;
		case 1:
			start = 9;
			break;
		case 2:
			start = 19;
			break;
		case 3:
			start = 28;
			break;
		case 4:
			start = 38;
			break;
		case 5:
			start = 47;
			break;
	}

	for(i = start; i < start + 7; i++){
		for(j = 0; j < 9; j++){
			board[i][j] = fnc[i - start][j];
		}
	}
}

void showBOARD(char board[][9]){
	int i, j;
	for(j = 0; j < 9; j++){
		if(j >= 0 && j <= 2){
			printf("   ");
		}
		if(j >= 3 && j <= 5){
			printf("  ");
		}
		if(j >= 6 && j <= 9){
			putchar(' ');
		}
		for(i = 0; i < 54; i++){
			putchar(board[i][j]);
		}
		putchar('\n');
	}
}

//seaerate integer that's max radix is 2
//ex) num is 45 and radix is 2, return 4
int seperateInteger(int num, int radix){
	int ret = 0;
	if(num < 10){
		ret = num;
	}else{
		if(radix == 2){
			ret = num / 10;
		}
		if(radix == 1){
			ret = num - (num/10) * 10;
		}
	}
	return ret;
}

void delay(clock_t n){
	clock_t start = clock();
	while ((clock() - start) / (CLOCKS_PER_SEC/1000) < n);
}


int main(){
	int ntime[3];
	int dgtNum, i, j;
	int radix = 2;
	
	char digit[7];
	char fnc[7][9];
	char board[54][9];
	
	int toc = 0;
	
	struct tm *t;
	time_t timer;
	
	for(i = 0; i < 54; i++) {
		for(j = 0; j < 9; j++) {
			board[i][j] = ' ';
		}
	}
	
	while(1){
		timer = time(NULL);
		t = localtime(&timer);
		
		ntime[0] = t->tm_hour;
		ntime[1] = t->tm_min;
		ntime[2] = t->tm_sec;
		
		if(ntime[0] < 10){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[0],2);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 0);
		
		if(ntime[0] == 0){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[0],1);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 1);
		
		if(ntime[1] < 10){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[1],2);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 2);
		
		if(ntime[1] == 0){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[1],1);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 3);
		
		if(ntime[2] < 10){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[2],2);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 4);
		
		if(ntime[2] == 0){
			dgtNum = 0;
		} else {
			dgtNum = seperateInteger(ntime[2],1);
		}
		convertEightDigit(dgtNum, digit);	convertFNC(fnc, digit);
		copyFNCtoBOARD(board, fnc, 5);
		
		if(toc == 0){
			board[17][2] = '|';
			board[17][6] = '|';
			board[36][2] = '|';
			board[36][6] = '|';
			toc = 1;
		}else{
			board[17][2] = '-';
			board[17][6] = '-';
			board[36][2] = '-';
			board[36][6] = '-';
			toc = 0;
		}
		system("clear");
		showBOARD(board);
		delay(500);
	}

		
}











