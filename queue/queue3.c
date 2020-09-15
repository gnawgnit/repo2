//不用链表表头实现队列
#include <stdio.h>
#include <stdlib.h>
#include "queue3.h"
//指向队列的第一个位置的指针
typedef Queue *QueueHead;

int IsEmpty(QueueHead H){
	return *H == NULL? 1 : 0;
}
int IsFull(QueueHead H){
	;
}
void MakeEmpty(QueueHead H);
QueueHead CreateQueue(void){
	QueueHead H;
	H = malloc(sizeof(Queue));
	if(H == NULL){
		Error("Not creat QueueHead");
		exit(EXIT_FAILURE);
	}
	MakeEmpty(H);
	return H;
}
void Dequeue(QueueHead H);
void DisposeQueue(QueueHead H){
	while((*H) != NULL){
		Dequeue(H);
	}
}
void MakeEmpty(QueueHead H){
	*H = NULL;
}
void Dequeue(QueueHead H){
	if(IsEmpty(H)){
		Error("Queue is empty");
		exit(EXIT_FAILURE);
	}
	Queue tmp = *H;
	*H = (*H)->Next;
	free(tmp);
}
void Enqueue(ElementType X, QueueHead H){
	while(*H != NULL){
		H = &((*H)->Next);
	}
    /*while(H != NULL)
        H = (*H)->Next;
        */
	Queue rear = malloc(sizeof(struct QueueRecord));
	if(rear == NULL){
		Error("Out of space");
		exit(EXIT_FAILURE);
	}
	rear->Data = X;
	rear->Next = NULL;

	*H = rear;
    
}
ElementType Front(QueueHead H){
	if(IsEmpty(H)){
		Error("Queue is empty");
		exit(EXIT_FAILURE);
	}
	
	return (*H)->Data;
}

ElementType FrontAndDequeue(QueueHead H){
	if(IsEmpty(H)){
		Error("Queue is empty");
		exit(EXIT_FAILURE);
	}
	ElementType rev;
	rev = (*H)->Data;
	Queue tmp = *H;
	*H = (*H)->Next;
	free(tmp);	
	return rev;
}
int main(void){
	QueueHead Q;
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
	Enqueue(29, Q);
	DisposeQueue(Q);
	printf("evething be ok");
	return 0;
}
