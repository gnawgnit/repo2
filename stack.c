//2020 7 16 周四
//数组实现 栈
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
Stack 
CreateStack(int MaxElements){
	Stack S;

	if(MaxElements < MinStackSize)
		Error("Stack siza is too small");
	S = (struct StackRecord *)malloc(sizeof(struct StackRecord));
		if(!S)
			Error("Out of space");
	S->Array = (ElementType *)malloc(sizeof(ElementType)*MaxElements);
	if(S->Array == NULL)
		Error("Out of space");

	S->Capacity = MaxElements;
	MakeEmpty(S);

	return S;

}
void MakeEmpty(Stack S){
	S->TopOfStack = EmptyTOS;
}
int IsEmpty(Stack S){
	return S->TopOfStack == EmptyTOS;
}
int IsFull(Stack S){
	return S->TopOfStack == S->Capacity;
}
void DisposeStack(Stack S){
	if(S != NULL){
		free(S->Array);
		free(S);
	}
}
void Push(ElementType X, Stack S){
	if(IsFull(S))
		Error("Full Stack");
	S->Array[++S->TopOfStack] = X;
}
ElementType Top(Stack S){
	if(IsEmpty(S)){
		Error("Empty Stack");
		return 0;
	}
	return S->Array[S->TopOfStack];
}
void Pop(Stack S){
	if(IsEmpty(S))
		Error("Empty Stack");
	else
		S->TopOfStack--;
}
ElementType TopAndPop(Stack S){
	if(IsEmpty(S)){
		Error("Empty Stack");
		return 0;
	}
	return S->Array[S->TopOfStack--];
}

int main(void){
	Stack S = CreateStack(10);
	Push(999, S);
	Push(990, S);
	Push(995, S);
	Push(949, S);
	Push(699, S);
	Push(959, S);
	Push(969, S);
	Push(899, S);
	Push(994, S);
	Push(979, S);

	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	printf("%d\n", TopAndPop(S));
	return 0;
}
