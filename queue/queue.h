#ifndef _Queue_h

typedef int ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef int ElementType;

int IsEmpty(Queue Q);
int IsFull(Queue Q);
//Queue CreateQueue(int MaxElements)
Queue CreateQueue(void);
void DisposeQueue(Queue Q);
void MakeEmpty(Queue Q);
void Enqueue(ElementType X, Queue Q);
ElementType Front(Queue Q);
void Dequeue(Queue Q);
ElementType FrontAndDequeue(Queue Q);

#endif /*_Queue_h*/

#define MinQueueSize (5)
#define DEFAULT (0)
/*struct QueueRecord{
	int Capacity;
	int Front;
	int Rear;
	int Size;
	ElementType *Array;
};数组实现所用结构*/

/*链表实现所用结构*/
struct QueueRecord{
	ElementType Data;
	Queue Next;
};
void Error(const char *str){
	printf("%s\n", str);
}
