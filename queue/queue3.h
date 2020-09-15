#ifndef _Queue_h

typedef int ElementType;
struct QueueRecord;
typedef struct QueueRecord *Queue;
typedef Queue *QueueHead;

int IsEmpty(QueueHead Q);
int IsFull(QueueHead Q);
//Queue CreateQueue(int MaxElements)
QueueHead CreateQueue(void);
void DisposeQueue(QueueHead Q);
void MakeEmpty(QueueHead Q);
void Enqueue(ElementType X, QueueHead Q);
ElementType Front(QueueHead Q);
void Dequeue(QueueHead Q);
ElementType FrontAndDequeue(QueueHead Q);

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
