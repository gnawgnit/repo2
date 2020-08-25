#include <stdio.h>
#include <stdlib.h>
#include "hashtbl.h"

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
//散列函数
Index Hash(const int Key, int TableSize){
	return Key%TableSize;
}

HashTable InitializeTable(int TableSize){
	HashTable H;
	int i;

	if(TableSize < MinTableSize){
		Error("Table size is too small");
		return NULL;
	}

	H = malloc(sizeof(struct HashTbl));
	if(H == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	H->TableSize = NextPrime(TableSize);
	//printf("%d\n", H->TableSize);

	H->TheLists = malloc(sizeof(List)*H->TableSize);
	if(H->TheLists == NULL){
		Error("Out of space");
		return NULL;
	}

	/*H->TheLists = malloc(sizeof(struct ListNode)*H->TableSize);
	for(i = 0;i < H->TableSize;i++){
		if(H->TheLists == NULL){
			Error("Out of space");
			return NULL;
		}
		else
			H->TheLists[i]->Next = NULL;
	}
	
	*/
	for(i = 0;i < H->TableSize;i++){
		H->TheLists[i] = malloc(sizeof(struct ListNode));
		if(H->TheLists[i] == NULL){
			Error("Out of space");
			exit(EXIT_FAILURE);
		}
		else
			H->TheLists[i]->Next = NULL;
	}
	return  H;
}
void DestoryList(List L){
	Position CellTmp;
	while(L->Next != NULL){
		CellTmp = L->Next->Next;
		free(L->Next);
		L->Next = CellTmp;
	}	
	free(L);
}
void DestoryTable(HashTable H){
	int i;
	for(i = 0;i < H->TableSize;i++)
		DestoryList(H->TheLists[i]);
	free(H);
}
Position Find(ElementType Key, HashTable H){
	Position P;
	List L;

	L = H->TheLists[Hash(Key, H->TableSize)];
	P = L->Next;
	while(P != NULL&&P->Element != Key)//maybe need strcmp
		P = P->Next;
	return P;
}
void Insert(ElementType Key, HashTable H){
	Position Pos, NewCell;
	List L;

	Pos = Find(Key, H);
	if(Pos == NULL){
		NewCell = malloc(sizeof(struct ListNode));
		if(NewCell == NULL){
			Error("Out of space");
			exit(EXIT_FAILURE);
		}
		else{
			L = H->TheLists[Hash(Key, H->TableSize)];
			NewCell->Next = L->Next;
			NewCell->Element = Key;
			L->Next = NewCell;
		}
	}
}
void Delete(ElementType Key, HashTable H){
	Position Pos, CellTmp;
	List L;

	Pos = Find(Key, H);
	if(Pos != NULL){
		L = H->TheLists[Hash(Key, H->TableSize)];
		CellTmp = L;	
		while(CellTmp->Next->Element != Key)//不用判断NULL,Pos!=NULL
			CellTmp = CellTmp->Next;
		//此时，CellTmp是Pos的前一节点
		CellTmp->Next = Pos->Next;
		free(Pos);
	}
	else
		;//啥也不做
}

ElementType Retrieve(Position P){
	if(P == NULL)
		return 0;
	return P->Element;
}
//驱动测试程序
int main(void){
	HashTable H;
	H = InitializeTable(24);
	Insert(1, H);
	Insert(4, H);
	Insert(9, H);
	Insert(34, H);
	Insert(89, H);
	Insert(76, H);
	Insert(108, H);
	Insert(245, H);
	printf("%d\n", Retrieve(Find(89, H)));
	Delete(89, H);
	printf("%d\n", Retrieve(Find(89, H)));
	DestoryTable(H);
	return 0;
}
/*运行结果:
89
0*/

