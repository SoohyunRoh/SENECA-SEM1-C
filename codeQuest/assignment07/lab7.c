#include <stdio.h>
#include <time.h>

//Generate item. Roll random number for item and add it.
void Generate_Item(int id[], int quantity[], int size){
	int item;
	int result;
	item = getRandom(0,4);
	result = Add_Item(id, quantity, size, item);
	if(result == 1){
		printf("\nNew Item Added!\n");
	} else {
		printf("\nInventory is already full!\n");
	}
}

//Add new item to inventory
//If same item already exist in id[], increase quantity + 1
//If item no exist in id[], try to find empty space in id[]
//If find empty space in id[], set item code and set 1 to quantity[location]
//return: 1-add item. 2-add item fail
int Add_Item(int id[], int quantity[], int size, int item){
	int location;
	int ret = 0;
	location = Find_Item(id, size, item);
	if(location > -1){	//Find same item in array
		quantity[location] = quantity[location] + 1;
		ret = 1;
	} else {			//Did't find same item in array

		location = Find_Item(id, size, -1);
		if(location > -1){		//Find empty space in array
			id[location] = item;
			quantity[location] = 1;
			ret = 1;
		}
	}
	return ret;
}

//Use (remove) item in array id[]
//return: 1-use item, 2-can't find item in array.
int Use_Item(int id[], int quantity[], int size, int item){
	int location;
	int ret = 0;
	location = Find_Item(id, size, item);
	
	if(location > -1){					//Find item in array
		if(quantity[location] > 0){		//Exist item
			quantity[location] = quantity[location] - 1;	//Use item
			printf("Item used!\n");
			ret = 1;
		}
		if(quantity[location] == 0){	//If use all of item, id[location] set empty
			id[location] = -1;
		}
		
	}else{
		printf("You don't have that item!\n");
	}
	return ret;
}

//Find item by given item number
//return location number in array
int Find_Item(int id[], int size, int item){
	int i = 0;
	int ret = -1;
	for(i = 0; i < size; i++){
		if(id[i] == item) ret = i;
	}
	return ret;
}

void Print_Item(int item){
	if(item >= 0 && item <= 4){
		if(item == 0){
			printf("Potion");
		} else if(item == 1){
			printf("HP Booster");
		} else if(item == 2){
			printf("Strength Booster");
		} else if(item == 3){
			printf("Defense Booster");
		} else if(item == 4){
			printf("Intelligence Booster");
		}
	}
}

void showInventory(int id[], int quantity[], int size){
	int i;
	for(i = 0; i < size; i++){
		if(id[i] >= 0){
			printf("%d. ", id[i]);
			Print_Item(id[i]);
			printf(" X%d\n", quantity[i]);
		}
	}
	printf("\n");
}

void initRandom(){
	time_t t;
	srand((unsigned)time(&t));
}

int getRandom(int min, int max){
	return min + (rand() % ((max + 1) - min));
}

void flush(){
	while(getchar() != '\n');
}

int getValidInput(int low, int high){
	int in;
	while(1){
		scanf("%d", &in);
		flush();
		if(in < low || in > high){
			printf("Invalid input. Try again: ");
		}else{
			return in;
		}
	}
	return -1;
}

int main(){
	int in, i;
	int id[3];
	int quantity[3];
	int size = 3;
	int citem;
	
	initRandom();
	for(i = 0; i < size; i++){
		id[i] = -1;
		quantity[i] = 0;
	}
	
	while(1){
		printf("1. Get New Item\n");
		printf("2. Show Inventory\n");
		printf("3. Use Item\n");
		printf("4. Quit\n\n");
		printf("Select Option: ");
		in = getValidInput(1, 4);
		
		if(in == 1){
			Generate_Item(id, quantity, size);
		} else if(in == 2){
			showInventory(id, quantity, size);
		} else if(in == 3){
			printf("Select item: ");
			citem = getValidInput(0, 5);
			Use_Item(id, quantity, size, citem);
		} else if(in == 4){
			break;
		}
	}
}