#include <stdio.h>
#include <string.h>

#define MAX_STR 5
#define MAX_CHAR 10

void flush(){
	while(getchar() != '\n');
}

int Validate_Alphanumberic (const char str[]){
	int i = 0;
	
	while(str[i] != '\0'){		//Allowed a~z, A~Z, 0~9, whitespace
		if(	(str[i] >= 'a' && str[i] <= 'z') ||
			(str[i] >= 'A' && str[i] <= 'Z') ||
			(str[i] >= '0' && str[i] <= '9') ||
			str[i] == ' ') {
				i++;
			} else return 0;	//String contains invalid character
	}
	return 1;	//String is valid
}

void Get_Valid(char str[]){
	char tmpStr[256];
	int validChk;

	do {
		scanf("%10[^\n]", tmpStr);	//Get String
		flush();
		validChk = Validate_Alphanumberic(tmpStr);
		if(validChk == 0){
			printf("Invalid, try again: ");
		} else {
			break;
		}
	} while(1);
	strcpy(str, tmpStr);			//Copy tmpStr to str
}

int main(){
	int result[MAX_STR];
	char str[MAX_STR][11];
	int i;
	
	printf("Please enter items names\n");
	for(i = 0; i < MAX_STR; i++){		//Get string from prompt
		printf("Item %d: ", i + 1);
		Get_Valid(str[i]);
	}
	
	for(i = 0; i < MAX_STR; i++)		//Print out strings
		printf("%d - %s\n", i, str[i]);
}
