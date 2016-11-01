#include <stdio.h>
#include <time.h>
#include <string.h>

#define TIME_PASS_NORTH_AND_SOUTH 40
#define TIME_PASS_WEST_AND_EAST 30
#define TIME_IDLE_YELLOW 5
#define TIME_WALKER_SAFE 5
#define TIME_WALKER_UNSAFE 20

#define C_DEFAULT 0
#define C_RED 31
#define C_GREEN 32
#define C_YELLOW 33
#define C_WHITE 37
#define C_MAGENTA 35

#define SPEED 1000

//0 to 999 integet convert to char*
void itoa(int in, char* string){
	int dgt = 1;
	int div = 1;
	int i;
	int z;
	if(in >= 10){dgt = 2;div=10;}
	else if(in >= 100){dgt = 3;div=100;}
	for(i = 0; i < dgt; i++){
		z = in / div + 48;
		*(string+i) = (char)z;	//ascii code
		in = in - (in / div * div);
		div = div / 10;
	}
	*(string+i) = '\0';
}


void drawMap(int data[], int tic[], int toc){
	system("clear");

	int cWNS;	//color for cross north and south walker signal
	int cWEW;	//color for cross east and west walker signal
	int cCNS;	//color for north and south signal
	int cCEW;	//color for east and west walker signal
	
	int nWNS = 0;	//counter for cross north and south walker signal
	int nWEW = 0;	//counter for cross east and west walker signal

	char sNSR = '@';	//red or yellow light for north and south
	char sNSG = '@';	//green light for north and south
	char sEWR = '@';	//red or yellow light for east and west
	char sEWG = '@';	//green light for east and west

	char walkerSignCNS = '@';
	char walkerSignCEW = '@';
	
	char strCntCNS[3];
	char strCntCEW[3];

	if(data[0] == 0){	//green for north and south
		cCNS = C_GREEN;
		sNSR = ' ';
	}else if(data[0] == 1){	//yellow for north and south
		cCNS = C_YELLOW;
		sNSG = ' ';
	}else if(data[0] == 2){	//red for north and south
		cCNS = C_RED;
		sNSG = ' ';
	}
	if(data[1] == 0){	//green for east and west
		cCEW = C_GREEN;
		sEWR = ' ';
	}else if(data[1] == 1){	//yellow for east and west
		cCEW = C_YELLOW;
		sEWG = ' ';
	}else if(data[1] == 2){	//red for east and west
		cCEW = C_RED;
		sEWG = ' ';
	}
	

	if(data[2] == 1){	//Crossing north and south line is unsafe
		nWNS = TIME_WALKER_UNSAFE + TIME_WALKER_SAFE - tic[2];// - TIME_WALKER_SAFE;
		itoa(nWNS, strCntCNS);
	} else {
		strcpy(strCntCNS,"  ");
	}
	if(data[3] == 1){	//Crossing east and west line is unsafe
		nWEW = TIME_WALKER_UNSAFE + TIME_WALKER_SAFE - tic[3];// - TIME_WALKER_SAFE;
		itoa(nWEW, strCntCEW);
	} else {
		strcpy(strCntCEW,"  ");
	}
	
	if(data[2] == 0){	//Cross north and south line allowed
		cWNS = C_GREEN;
	} else {
		cWNS = C_RED;
		if(toc == 1 && nWNS > 0)walkerSignCNS = ' ';
	}
	if(data[3] == 0){	//Cross east and west line allowed
		cWEW = C_GREEN;
	} else {
		cWEW = C_RED;
		if(toc == 1 && nWEW > 0)walkerSignCEW = ' ';
	}

	printf("                        |     |     |           North-South green light term: %dsec\n", TIME_PASS_NORTH_AND_SOUTH);
	printf("                        |           |           East-West green light term: %dsec\n", TIME_PASS_WEST_AND_EAST);
	printf("                        |     |     |           Yello light term: %dsec\n", TIME_IDLE_YELLOW);
	printf("                        |           |           Walker light term(safe)  : %dsec\n", TIME_WALKER_SAFE);
	printf("                        |     |     |           Walker light term(unsafe): %dsec\n", TIME_WALKER_UNSAFE);
	printf("                   [%2s]%c[%dm%c%c[%dm#############%c[%dm%c%c[%dm[%2s]\n", strCntCNS, 27, cWNS, walkerSignCNS, 27, C_DEFAULT, 27, cWNS, walkerSignCNS, 27, C_DEFAULT, strCntCNS);
	printf("                        |           |\n");
	printf("               [%2s]%c[%dm%c%c[%dm    |       %c[%dm%c%c%c[%dm  |    %c[%dm%c%c[%dm[%2s]\n", strCntCEW, 27, cWEW, walkerSignCEW, 27, C_DEFAULT, 27, cCNS, sNSG, sNSR, 27, C_DEFAULT, 27, cWEW, walkerSignCEW, 27, C_DEFAULT, strCntCEW);
	printf("-------------------#----+  -------  +----#-------------------\n");
	printf("                   # %c[%dm%c%c[%dm                   #\n", 27, cCEW, sEWG, 27, C_DEFAULT);
	printf("                   # %c[%dm%c%c[%dm  |           |    #\n", 27, cCEW, sEWR, 27, C_DEFAULT);
	printf("--  --  --  --  -- #    |           |    # --  --  --  --  --\n");
	printf("                   #    |           | %c[%dm%c%c[%dm  #\n", 27, cCEW, sEWR, 27, C_DEFAULT);
	printf("                   #                  %c[%dm%c%c[%dm  #\n", 27, cCEW, sEWG, 27, C_DEFAULT);
	printf("-------------------#----+  -------  +----#-------------------\n");
	printf("               [%2s]%c[%dm%c%c[%dm    |  %c[%dm%c%c%c[%dm       |    %c[%dm%c%c[%dm[%2s]\n", strCntCEW, 27, cWEW, walkerSignCEW, 27, C_DEFAULT, 27, cCNS, sNSG, sNSR, 27, C_DEFAULT, 27, cWEW, walkerSignCEW, 27, C_DEFAULT, strCntCEW);
	printf("                        |           |\n");
	printf("                   [%2s]%c[%dm%c%c[%dm#############%c[%dm%c%c[%dm[%2s]\n", strCntCNS, 27, cWNS, walkerSignCNS, 27, C_DEFAULT, 27, cWNS, walkerSignCNS, 27, C_DEFAULT, strCntCNS);
	printf("                        |     |     |        toc               : %3d\n", toc);
	printf("                        |           |        tic 1(North-South): %3d (Car)\n", tic[0]);
	printf("                        |     |     |        tic 2(East-West)  : %3d (Car)\n", tic[1]);
	printf("                        |           |        tic 3(North-South): %3d (Walker)\n", tic[2]);
	printf("                        |     |     |        tic 4(East-West)  : %3d (Walker)\n", tic[3]);

}

void delay(clock_t n){
	clock_t start = clock();
	while ((clock() - start) / (CLOCKS_PER_SEC/1000) < n);
}

void signalAdjust(int data[], int tic[]){
	

	if(data[0] == 0 && (tic[0] == TIME_PASS_NORTH_AND_SOUTH - TIME_IDLE_YELLOW)){
		data[0] = 1;	//change green to yellow at north to south line
	}
	if(data[1] == 0 && (tic[1] == TIME_PASS_WEST_AND_EAST - TIME_IDLE_YELLOW)){
		data[1] = 1;	//change green to yellow at east to west line
	}
	if(data[0] == 1 && (tic[0] == TIME_PASS_NORTH_AND_SOUTH)){
		data[0] = 2;	//change yellow to red at north to south line
	}
	if(data[1] == 1 && (tic[1] == TIME_PASS_WEST_AND_EAST)){
		data[1] = 2;	//change yellow to red at east to west line
	}
	
	if(data[0] == 2 && (tic[1] == TIME_PASS_WEST_AND_EAST)){
		data[0] = 0;	//change red to green at north to south line
		data[3] = 0;	//change to green for walker signal					
	}

	if(data[1] == 2 && (tic[0] == TIME_PASS_NORTH_AND_SOUTH)){
		data[1] = 0;	//change red to green at east to west line
		data[2] = 0;	//change to green for walker signal
	}

	if(data[2] == 0 && tic[2] == TIME_WALKER_SAFE){
		data[2] = 1;
	}
	if(data[3] == 0 && tic[3] == TIME_WALKER_SAFE){
		data[3] = 1;
	}
	if(data[2] == 1 && tic[2] == TIME_WALKER_SAFE + TIME_WALKER_UNSAFE){
		data[2] = 2;
	}
	if(data[3] == 1 && tic[3] == TIME_WALKER_SAFE + TIME_WALKER_UNSAFE){
		data[3] = 2;
	}

	
	if(data[0] != 2){
		tic[0]++;
	}
	if(data[1] != 2){
		tic[1]++;
	}
	if(data[2] != 2){
		tic[2]++;
	}
	if(data[3] != 2){
		tic[3]++;
	}
	
	if(data[0] == 2){
		tic[0] = 0;
	}
	if(data[1] == 2){
		tic[1] = 0;
	}
	if(data[2] == 2){
		tic[2] = 0;
	}
	if(data[3] == 2){
		tic[3] = 0;
	}
	

}

int main(){
	int data[4] = {2,0,0,2};
		//Car signal:North-South, East-West
		//Walker signal: North-South, East-West
		//Car 0:green, 1:yello, 2:red
		//Walker 0:pass, 1:unsafe, 2:denined
	int tic[4] = {0};
		//TIC: 	CAR [0]strait N-S, [1]strait E-W
		//	WLK [2]cross N-S, [3]cross E-W
	int toc = 0;
	while(1){
		drawMap(data, tic, toc);
		if(toc == 0)signalAdjust(data, tic);
		delay(SPEED / 2);
		if(toc == 0)toc = 1;
		else toc = 0;
	}
	
		
}
