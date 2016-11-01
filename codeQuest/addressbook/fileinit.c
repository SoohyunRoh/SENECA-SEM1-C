#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define PAGEPERITEM 20

typedef struct record {
	char name[22];
	char cellphone[22];
	char memo[22];
} RECORD;

//FILE INITIALIZE
void initFile(FILE *fh){
	if((fh = fopen("data.txt","r")) == NULL){			//read mode
		printf("STATUS : NO EXIST FILE [data.txt]\n");
		printf("STATUS : CREATE FILE [data.txt]\n");
		if((fh = fopen("data.txt","w")) == NULL){		//write mode
			printf("ERROR : CREATE DATA FILE");
		} else {
			printf("STATUS : SUCCESS\n");
		}
	}
	fclose (fh);
}

//PRINT ONE RECORD
void printfRecord(int no, char *name, char *cellphone, char *memo){
	int sizeOfName = (int)strlen(name);
	int sizeOfCellPhone = (int)strlen(cellphone);
	int sizeOfMemo = (int)strlen(memo);

	printf("|%d\t|%s\t", no, name);
	if(sizeOfName < 15) printf("\t");
	if(sizeOfName < 7) printf("\t");

	printf("|%s\t", cellphone);
	if(sizeOfCellPhone < 15) printf("\t");
	if(sizeOfCellPhone < 7) printf("\t");

	printf("|%s\t", memo);
	if(sizeOfMemo < 15) printf("\t");
	if(sizeOfMemo < 7) printf("\t");
	printf("|\n");
}

//CLEAR INPUT BUFFER
void flush(){
	while(getchar() != '\n');
}

//SHOW TITLE OF LIST AND ITEMS LIST
int showList(FILE *fh, RECORD *r, int items, int start, int end){
	int i;
	int retVal = 0;

	printf("---------------------------------------------------------------------------------\n");
	printf("|No\t|Name\t\t\t|Cell Phone\t\t|Memo\t\t\t|\n");
	printf("---------------------------------------------------------------------------------\n");
	if(items > 0){
		for(i = start; i <= end; i++){
			printfRecord(i, r[i - 1].name, r[i - 1].cellphone, r[i - 1].memo);
		}
	} else {
		printf("                                     No data\n");
	}
	printf("---------------------------------------------------------------------------------\n");
	
	if(items > 0){
		if(start != 1){
			printf("[P]revious page\t");
			retVal += 2;
		}
		if(end != items){
			printf("[N]ext page\t");
			retVal += 1;
		}
		printf("[D]elete\t[M]odify\n");
	}

	// 0-00 : only one list
	// 1-01 : next ok
	// 2-10 : pre ok
	// 3-11 : pre ok, next ok
	return retVal;
}

//SHOW MENU ADD OR QUIT
char printCMenu(){
	char cmnd;
	printf("[A]dd record\t[Q]uit\n");
	printf("Input command :");
	scanf("%c", &cmnd);
	flush();
	return cmnd;
}

//GET RANGED SELECTION
int printDMenu(int start, int end, char cmenu){
	int number;
	if(cmenu == 'D' || cmenu == 'd'){
		printf("Input record No. for Delete [%d ~ %d] :", start, end);
	} else if(cmenu == 'M' || cmenu == 'm'){
		printf("Input record No. for Modify [%d ~ %d] :", start, end);
	}
	scanf("%d", &number);
	flush();
	return number;
}

//GET NEW DATA FROM CONSOLE
RECORD getNewItem(){
	char tmpName[22] = {};
	char tmpCellphone[22] = {};
	char tmpMemo[22] = {};
	RECORD retRcrd = {};
	
	printf("---------------------------------------------------------------------------------\n");
	printf("Input new data\n");
	printf("---------------------------------------------------------------------------------\n");
	
	printf("Name [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpName);
	flush();
	printf("Cell phone [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpCellphone);
	flush();
	printf("Memo [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpMemo);
	flush();
	
	strcpy(retRcrd.name, tmpName);
	strcpy(retRcrd.cellphone, tmpCellphone);
	strcpy(retRcrd.memo, tmpMemo);
	
	return retRcrd;
}

//CONFIRM Y/N (RETURN Y:1/N:0)
int confirmAsk(){
	int retVal = 0;
	char cnf;
	printf("Are you sure ? [Y / N]");
	scanf("%c",&cnf);
	flush();
	if(cnf == 'Y' || cnf == 'y') retVal = 1;
	else if(cnf == 'N' || cnf == 'n') retVal = 0;
	else return confirmAsk();
	return retVal;
}

//PUT DATA INTO FILE
void addFile(FILE *fh, RECORD newRecord){
	if((fh = fopen("data.txt","a")) == NULL){			//add mode
		printf("ERROR : NO EXIST FILE [data.txt]\n");
	} else {
		fprintf(fh, "%s\n", newRecord.name);
		fprintf(fh, "%s\n", newRecord.cellphone);
		fprintf(fh, "%s\n", newRecord.memo);
		
		fclose(fh);
	}
}

//COUNTING NUMBER OR ITEM IN FILE
int getItemCount(FILE *fh){
	int cnt = 0;
	char buff[22] = {};
	if((fh = fopen("data.txt","r")) == NULL){
		printf("ERROR : NO EXIST FILE [data.txt]\n");
	} else {
		while(fgets(buff, sizeof(buff), fh)){
			cnt ++;
		}
		fclose(fh);
	}
	return cnt;
}

//DELETE ONE DATA FROM DATA SET AND RE-WRITE FILE
void delFile(FILE *fh, RECORD *oldRcrd, int dmenu, int records){
	int i;
	if((fh = fopen("data.txt","w")) == NULL){
		return;
	}
	
	if(dmenu == 1 && records == 1){	//CASE OF DELETING LAST DATA
		fclose(fh);					//NOTHING TO DO
	} else if(dmenu == records) {	//CASE OF DELETING END OF DATA
		for(i = 0; i < records - 1; i++){	//ADD EXIST DATA TO FILE EXCEPT LAST RECORD
			fprintf(fh, "%s\n", oldRcrd[i].name);
			fprintf(fh, "%s\n", oldRcrd[i].cellphone);
			fprintf(fh, "%s\n", oldRcrd[i].memo);
		}
		fclose(fh);
	} else {						//CASE OF DELETING FIRST OR MIDDLE OF DATA
		for(i = 0; i < records; i++){
			if(i != (dmenu - 1)) {	//JUMP IF i IS NUMBER OF DELETE RECORD
				fprintf(fh, "%s\n", oldRcrd[i].name);
				fprintf(fh, "%s\n", oldRcrd[i].cellphone);
				fprintf(fh, "%s\n", oldRcrd[i].memo);
			}
		}
		fclose(fh);
	}
	printf("Delete Complete. [Press any key]\n");
	getchar();
}

//Modify Record
void modFile(FILE *fh, RECORD *oldRcrd, int dmenu, int records){
	int i;
	char tmpName[22] = {};
	char tmpCellphone[22] = {};
	char tmpMemo[22] = {};
	
	dmenu--;

	printf("-----------------------------------------------\n");
	printf("                 Previous Data                 \n");
	printf("-----------------------------------------------\n");
	printf("Name : %s\n", oldRcrd[dmenu].name);
	printf("Cell Phone : %s\n", oldRcrd[dmenu].cellphone);
	printf("Memo : %s\n", oldRcrd[dmenu].memo);
	printf("-----------------------------------------------\n");
	printf("                    New Data                   \n");
	printf("-----------------------------------------------\n");
	printf("Name [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpName);
	flush();
	printf("Cell phone [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpCellphone);
	flush();
	printf("Memo [maximum 22 character]: ");
	scanf("%22[^\n]s", &tmpMemo);
	flush();
	
	if(confirmAsk() == 1) {
		if((fh = fopen("data.txt","w")) == NULL){
			return;
		}
		strcpy(oldRcrd[dmenu].name, tmpName);
		strcpy(oldRcrd[dmenu].cellphone, tmpCellphone);
		strcpy(oldRcrd[dmenu].memo, tmpMemo);

		for(i = 0; i < records; i++){	
			fprintf(fh, "%s\n", oldRcrd[i].name);
			fprintf(fh, "%s\n", oldRcrd[i].cellphone);
			fprintf(fh, "%s\n", oldRcrd[i].memo);	
		}
		fclose(fh);
	}
}

//GET DATA FROM FILE AND PUT INTO DATA SET
void getItems(FILE *fh, RECORD *rcrd, int records){
	char buff[22] = {};
	int cnt = 0;
	if((fh = fopen("data.txt","r")) == NULL){
		printf("ERROR : NO EXIST FILE [data.txt]\n");
	} else {
		while(cnt < records){
			fgets(buff, sizeof(buff)+1, fh);	//READ FROM FILE (NAME)	
			buff[strlen(buff) - 1] = '\0';		//CONVERT TO STRING DATA TYPE
			strcpy(rcrd[cnt].name, buff);		//PUT INTO DATA SET
			
			fgets(buff, sizeof(buff)+1, fh);	//READ FROM FILE (CELLPHONE)	
			buff[strlen(buff) - 1] = '\0';		//CONVERT TO STRING DATA TYPE
			strcpy(rcrd[cnt].cellphone, buff);	//PUT INTO DATA SET
			
			fgets(buff, sizeof(buff)+1, fh);	//READ FROM FILE (MEMO)
			buff[strlen(buff) - 1] = '\0';		//CONVERT TO STRING DATA TYPE
			strcpy(rcrd[cnt].memo, buff);		//PUT INTO DATA SET
			
			cnt++;
		}
		fclose(fh);
	}
}

int main () {
	FILE *fh;
	int stat = 0;			// LIST STATUS [0:nodata, 1:next, 2:prev, 3:prev and next]
	int start = 0;			// START ITEM NUMBER AT CURRENT LIST
	int end = 0;			// END ITEM NUMBER AT CURRENT LIST
	int exitCondition = 0;	// CONDITION OF EXIT PROGRAM
	int currentPage = 1;	// CURRENT PAGE NUMBER
	int records = 0;		// GET RECORD NUMBER FROM NUMBER OF LINE FROM FILE (recordCnt) DIVIDE BY ITEMS(3)
	int lmenu = 0;			// CURRENT SCREEN CODE NUMBER
	int dmenu = 0;			// NUMBER OF CURRENT SELECT RECORD
	
	initFile(fh);
	while(exitCondition == 0){
		char cmenu;

		records = getItemCount(fh) / 3;
		RECORD *oldRcrd;		// EXIST DATA FROM FILE
		RECORD newRcrd = {};	// NEW DATA FROM CONSOLE
		oldRcrd = (struct record*)malloc(sizeof(struct record) * records);
		getItems(fh, oldRcrd, records);
		int size = sizeof(oldRcrd) / sizeof(RECORD);

		system("clear");
		switch (lmenu) {
			case 0:	//Main menu
				start = PAGEPERITEM * (currentPage - 1) + 1;
				end = start + PAGEPERITEM - 1;
				if(end > records) end = records;
				printf("Address Book\t\t\t\t\tTotal records : %d\n", records);
				stat = showList(fh, oldRcrd, records, start, end);
				cmenu = printCMenu();

				if((cmenu == 'P' || cmenu =='p') && (stat == 2 || stat == 3)){
					currentPage -= 1;
				} else if((cmenu == 'N' || cmenu == 'n') && (stat == 1 || stat == 3)){
					currentPage += 1;
				} else if((cmenu == 'D' || cmenu == 'd' || cmenu == 'M' || cmenu == 'm')&& (records != 0)){
					dmenu = printDMenu(start, end, cmenu);
					if(dmenu < start || dmenu > end){
						printf("Error: Out of range \n Press any key");
						getchar();
					} else {
						if(cmenu == 'D' || cmenu == 'd'){
							lmenu = 2;
						} else if(cmenu == 'M' || cmenu == 'm'){
							lmenu = 3;
						}
					}
				} else if(cmenu == 'A' || cmenu == 'a'){
					lmenu = 1;
				} else if(cmenu == 'Q' || cmenu == 'q'){
					exitCondition = 1;
				}
				
				break;
			case 1:		//Add
				newRcrd = getNewItem();
				if(confirmAsk() == 1) {
					addFile(fh, newRcrd);
				}

				lmenu = 0;
				break;
			case 2:		//Delete
				if(confirmAsk() == 1) {
					delFile(fh, oldRcrd, dmenu, records);
				}
				lmenu = 0;	//BACK TO MAIN MENU
				break;
			case 3:		//Modify
				modFile(fh, oldRcrd, dmenu, records);
				lmenu = 0;	//BACK TO MAIN MENU
				break;
		}
		
		free(oldRcrd);

	}
	return 0;
	
	
}