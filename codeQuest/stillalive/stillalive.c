#include <stdio.h>
#include <time.h>
#include <string.h>

// SPEED 300	 
#define SPEED 250
#define FILENAME "ldata.txt"

void delay(int milsec) {
    long pause;
    clock_t start, end;
    pause = milsec*(CLOCKS_PER_SEC/1000);
    start = end = clock();
    while( (start - end) < pause ) start = clock();
}

void printSpread(char data[], int speed) {
	int len = strlen(data);
	double charSpeed = (SPEED / len);
	int i;
	for(i = 0; i < len; i++){
		if(data[i] != '\n'){
			printf("%c",data[i]);
		}
		delay( charSpeed );
	}
}

int main(){
	char lyric[14];
	char getS[20];
	char code;
	FILE *fp;

	//system("cls");
	system("clear");
	fp = fopen(FILENAME, "r");
	if(fp == NULL){
		printf("ERROR IN DATAFILE\n");
		return 0;
	}
	
	while(!feof(fp)){
		fscanf(fp, "%[^\t]\t%c", lyric, &code);
		fgetc(fp);

		if(strlen(lyric) > 0 && code != 'W'){

			printSpread(lyric, SPEED);
			if(code == 'S'){
				printf(" ");
			} else if(code == 'N') {
				printf("\n");
			} else if(code == 'C') {
				system("clear");
				//system("cls");
			}
		} else {
			delay( SPEED );
		}
		
	}
	fclose(fp);
	return 0;
}
