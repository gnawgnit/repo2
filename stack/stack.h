#ifndef _Stack_h

typedef int ElementType;
struct StackRecord;
typedef struct StackRecord *Stack;

int IsEmpty(Stack S);
int IsFull(Stack S);
Stack CreateStack(int MaxElements);
void DisposeStack(Stack S);
void MakeEmpty(Stack S);
void Push(ElementType X, Stack S);
ElementType Top(Stack S);
void Pop(Stack S);
ElementType TopAndPop(Stack S);

#endif   /* _Stack.h_   */
#define EmptyTOS (-1)
#define MinStackSize (5)

struct StackRecord{
	int Capacity;
	int TopOfStack;
	ElementType *Array;
};

void Error(const char *str){
	printf("%s\n", str);
}
