#include <stdio.h>
#include <stdlib.h>
#include "hashtbl2.h"

void Error(char *str){
	printf("%s\n", str);
}

int IsPrime(int number){
	int j = number/2 + 1;
	int i;
	for(i = 2;i <= j;i++){
		if(number%i == 0)
			return 0;//不是素数
	}
	return 1;//素数
}
int NextPrime(int TableSize){
	while(!IsPrime(TableSize))
		TableSize++;
	return TableSize;
}
Index Hash(ElementType Key, int TableSize){
	return Key%TableSize;
}
HashTable InitializeTable(int TableSize){
	HashTable H;
	int i;

	if(TableSize < MinTableSize){
		Error("The Table is too small");
		return NULL;
	}

	H = malloc(sizeof(struct HashTbl));
	if(H == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}

	H->TableSize = NextPrime(TableSize);

	H->TheCells = malloc(sizeof(struct HashEntry)*H->TableSize);
	if(H->TheCells == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}

	for(i = 0;i < H->TableSize;i++)
		H->TheCells[i].Info = Empty;

	return H;
}
Position Find(ElementType Key, HashTable H){
	Position CurrentPos;
	int CollisionNum;

	CollisionNum = 0;
	CurrentPos = Hash(Key, H->TableSize);
	while(H->TheCells[CurrentPos].Info != Empty&&H->TheCells[CurrentPos].Element != Key){
		CurrentPos += 2 * ++CollisionNum - 1;
		if(CurrentPos >= H->TableSize)
			CurrentPos -= H->TableSize;
	}
	return CurrentPos;
}
//装填因子
float FactorOfPriming(HashTable H){
	int i;
	float j = 0;
	for(i = 0;i < H->TableSize;i++)
		if(H->TheCells[i].Info == Legitimate)
			j++;  //legitimate  合法的
	return j/H->TableSize;
}
void Insert(ElementType Key, HashTable H){
/*	float Factor = FactorOfPriming(H);
	printf("Factor = %f\n", Factor);
	if(Factor > 0.5)
		H = Rehash(H);
*/	
	Position Pos;

	Pos = Find(Key, H);
	if(H->TheCells[Pos].Info != Legitimate){
		H->TheCells[Pos].Info = Legitimate;
		H->TheCells[Pos].Element = Key;//Maybe need strcmp
	}
}
HashTable Rehash(HashTable H){//再散列总是出错
	int i, OldSize;
	Cell *OldCells;

	OldCells = H->TheCells;
	OldSize = H->TableSize;
	H = InitializeTable(2 * OldSize);
	printf("check!\n");

	for(i = 0;i < OldSize;i++)
		if(OldCells[i].Info == Legitimate)
			Insert(OldCells[i].Element, H);
	
	free(OldCells);
	printf("check!\n");

	return H;
}
ElementType Retrieve(Position P, HashTable H){
	if(H->TheCells[P].Info != Legitimate)
		return -1;
	return H->TheCells[P].Element; //默认是有值的
}
void DestoryTable(HashTable H){
	free(H->TheCells);
	free(H);
}
int main(void){
	HashTable H = InitializeTable(24);
	printf("%d\n", H->TableSize);
	Insert(24, H);
	Insert(4, H);
	Insert(89, H);
	Insert(897, H);
	Insert(62, H);
	Insert(739, H);
	Insert(242, H);
	Position P = Find(897, H);
	printf("%d\n",Retrieve(P, H));
	printf("%d\n", H->TableSize);
	DestoryTable(H);
	return 0;
}
