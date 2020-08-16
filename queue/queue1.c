//用数组实现队列 不知道为啥将赋值语句写成==，害我看了半天
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
int IsEmpty(Queue Q){
	return Q->Size == 0;
}
int IsFull(Queue Q){
	return Q->Size == Q->Capacity;
}
Queue CreateQueue(int MaxElements){
	Queue Q;
	if(MaxElements < MinQueueSize){
		Error("too small");
		return NULL;
	}
	Q = (struct QueueRecord *)malloc(sizeof(struct QueueRecord));
	if(Q == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}

	Q->Array = (ElementType *)malloc(sizeof(ElementType)*MaxElements);
	if(Q->Array == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	Q->Capacity = MaxElements;
	MakeEmpty(Q);

	return Q;
}
void MakeEmpty(Queue Q){
	Q->Size = 0;
	Q->Front = 1;
	Q->Rear = 0;
}
void DisposeQueue(Queue Q){
	if(Q != NULL){
		free(Q->Array);
		free(Q);
	}
}
int Succ(int value, Queue Q){
	if(++value == Q->Capacity)
		value = 0;
	return value;
}
void Enqueue(ElementType X, Queue Q){
	if(IsFull(Q))
		Error("Queue is full");
	else{
		Q->Size++;
		Q->Rear = Succ(Q->Rear, Q);
		Q->Array[Q->Rear] = X;
	}
}
ElementType Front(Queue Q){
	if(IsEmpty(Q)){
		Error("Queue is empty");
		return 0;
	}
	return Q->Array[Q->Front];
}
void Dequeue(Queue Q){
	if(IsEmpty(Q)){
		Error("Queue is empty");
		return ;
	}
	Q->Size--;
	Q->Front++;
}

ElementType FrontAndDequeue(Queue Q){
	if(IsEmpty(Q)){
		Error("Queue is empty");
		return 0;
	}
	Q->Size--;
	return Q->Array[Q->Front++];
}
int main(void){
	Queue Q;
	Q = CreateQueue(10);
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
	Enqueue(29, Q);
	DisposeQueue(Q);
	return 0;
}
