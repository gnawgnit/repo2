//优先队列
#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

void Error(const char *str){
	printf("%s\n", str);
}
PriorityQueue Initialize(int MaxElements){
	PriorityQueue H;

	if(MaxElements < MinPQSize){
		Error("PriorityQueue is too small");
		return NULL;
	}

	H = malloc(sizeof(struct HeapStruct));
	if(H == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}

	H->Size = 0;
	H->Capacity = MaxElements;

	H->Elements = malloc(sizeof(ElementType) * MaxElements + 1);
	if(H->Elements == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	H->Elements[0] = MinData;

	return H;
}

int IsEmpty(PriorityQueue H){
	return !(H->Size);
}
int IsFull(PriorityQueue H){
	return H->Size < H->Capacity?0:1;
}
void Destory(PriorityQueue H){
	free(H->Elements);
	free(H);
}

void MakeEmpty(PriorityQueue H){
	H->Size = 0;
}

void Insert(ElementType X, PriorityQueue H){
	int i;
	if(IsFull(H)){
		Error("PriorityQueue is Full");
		return;
	}
	for(i = ++H->Size;H->Elements[i/2] > X;i /= 2)
		H->Elements[i] = H->Elements[i/2];
	H->Elements[i] = X;
}

ElementType FindMin(PriorityQueue H){
	return H->Elements[1];
}

ElementType DeleteMin(PriorityQueue H){
	int i, Child;
	ElementType MinElement, LastElement;

	if(IsEmpty(H)){
		Error("PriorityQueue is Empty");
		return H->Elements[0];
	}

	MinElement = H->Elements[1];
	LastElement = H->Elements[H->Size--];

	for(i = 1;2 * i <= H->Size;i = Child){
		Child = 2 * i;
		if(Child != H->Size && H->Elements[Child] > H->Elements[Child+1])
			Child++;
		if(H->Elements[Child] < LastElement)
			H->Elements[i] = H->Elements[Child];
		else
			break;
	}
	H->Elements[i] = LastElement;
	return MinElement;
}
int main(void){
	PriorityQueue H;
	H = Initialize(6);
	Insert(23, H);
	Insert(34, H);
	Insert(234, H);
	Insert(734, H);
	Insert(134, H);
	Insert(94, H);
	printf("%d\n", FindMin(H));
	DeleteMin(H);
	printf("%d\n", FindMin(H));
	DeleteMin(H);
	printf("%d\n", FindMin(H));
	Insert(279, H);
	Insert(56, H);
	Destory(H);
	return 0;
}
//测试成功
