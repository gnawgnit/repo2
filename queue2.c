//用链表实现队列
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
int IsEmpty(Queue Q){
	return Q->Next == NULL;
}
Queue CreateQueue(void){
	Queue Q;
	Q = malloc(sizeof(struct QueueRecord));
	if(!Q){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	MakeEmpty(Q);
	return Q;
}
void MakeEmpty(Queue Q){
	if(Q != NULL){
		Q->Data = DEFAULT;//哑值
		Q->Next = NULL;
	}
}
void DisposeQueue(Queue Q){
	if(Q != NULL){
		free(Q);
	}
}
void Enqueue(ElementType X, Queue Q){
	
	Queue New = malloc(sizeof(struct QueueRecord));
	if(!New){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	New->Data = X;
	New->Next = NULL;

	Queue Tmp = Q;
	while(Tmp->Next != NULL)
		Tmp = Tmp->Next;
	
	Tmp->Next = New;
}
ElementType FrontAndDequeue(Queue Q){
	if(IsEmpty(Q)){
		Error("Queue is empty");
		return 0;//
	}
	ElementType Tmpval = Q->Next->Data;
	Queue Tmp = Q->Next;
	Q->Next = Q->Next->Next;
	free(Tmp);
	return Tmpval;
}
ElementType Front(Queue Q){
	if(IsEmpty(Q)){
		Error("Queue is empty");
		return 0;//
	}
	return Q->Next->Data;
}
void Dequeue(Queue Q){
	if(IsEmpty(Q))
		Error("Queue is empty");
	Queue Tmp = Q->Next;
	Q->Next = Q->Next->Next;
	free(Tmp);
}
int main(void){
	Queue Q;
	Q = CreateQueue();
	Enqueue(20, Q);
	Enqueue(21, Q);
	Enqueue(22, Q);
	Enqueue(23, Q);
	Enqueue(24, Q);
	Enqueue(25, Q);
	Enqueue(26, Q);
	Enqueue(27, Q);
	Enqueue(28, Q);
	Enqueue(29, Q);
	Enqueue(29, Q);
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	printf("%d\n", FrontAndDequeue(Q));
	Enqueue(29, Q);
	DisposeQueue(Q);
	return 0;
}
