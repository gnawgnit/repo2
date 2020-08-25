#ifndef _BinHeap_H
#define _BinHeap_H

#define MinPQSize 5
#define MinData -520

typedef int ElementType;

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize(int MaxElements);
void Destory(PriorityQueue H);
void MakeEmpty(PriorityQueue H);
void Insert(ElementType X, PriorityQueue H);
ElementType FindMin(PriorityQueue H);
ElementType DeleteMin(PriorityQueue H);
int IsEmpty(PriorityQueue H);
int IsFull(PriorityQueue H);

#endif
struct HeapStruct{
	int Capacity;
	int Size;
	ElementType *Elements;
};
