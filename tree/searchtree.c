//二叉搜索树实现
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

SearchTree MakeEmpty(SearchTree T){
	if(T != NULL){
		MakeEmpty(T->Left);
		MakeEmpty(T->Right);
		free(T);
	}
	return NULL;
}
Position Find(ElementType X, SearchTree T){
	if(T == NULL)
		return NULL;
	if(X < T->Element)
		return Find(X, T->Left);
	else if(X > T->Element)
		return Find(X, T->Right);
	else
		return T;
}
Position FindMin(SearchTree T){
	if(T == NULL)
		return NULL;
	else if(T->Left == NULL)
		return T;
	else
		return FindMin(T->Left);
}
Position FindMax(SearchTree T){
	if(T != NULL)
		while(T->Right != NULL)
			T = T->Right;

	return T;
}
SearchTree Insert(ElementType X, SearchTree T){
	if(T == NULL){
		T = malloc(sizeof(struct TreeNode));
		if(T == NULL)
			Error("Out of space");
		else{
			T->Element= X;
			T->Left = T->Right = NULL;
		}
	}
	else if(X < T->Element)
		T->Left = Insert(X, T->Left);
	else if(X > T->Element)
		T->Right = Insert(X, T->Right);
	
	return T;
}
SearchTree Delete(ElementType X, SearchTree T){
	Position TmpCell;

	if(T == NULL)
		Error("Element not found");
	else if(X < T->Element)
		T->Left = Delete(X, T->Left);
	else if(X > T->Element)
		T->Right = Delete(X, T->Right);
	else if(T->Left && T->Right){
		TmpCell = FindMin(T->Right);
		T->Element= TmpCell->Element;
		T->Right = Delete(T->Element, T->Right);
	}
	else{
		TmpCell = T;
		if(T->Left == NULL)
			T = T->Right;
		else if(T->Right == NULL)
			T = T->Left;
		free(TmpCell);
	}
	return T;
}
//中序遍历
void PrintTree(SearchTree T){
	if(T == NULL)
		return ;

	PrintTree(T->Left);
	printf("%d\t", T->Element);
	PrintTree(T->Right);
}
int main(void){
	SearchTree T = NULL;
	T = MakeEmpty(T);
	T = Insert(32, T);
	T = Insert(2, T);
	T = Insert(20, T);
	T = Insert(82, T);
	T = Insert(92, T);
	T = Insert(37,T);
	T = Insert(56,T);
	T = Insert(78, T);
	T = Insert(35, T);
	T = Insert(67, T);
	T = Insert(34, T);
	T = Insert(29, T);
	T = Insert(12, T);

	PrintTree(T);
	printf("\n");
	printf("%d\n", FindMax(T)->Element);
	printf("%d\n", FindMin(T)->Element);
	printf("%d\n", Find(37, T)->Element);

	T = Delete(78, T);
	T = Delete(35, T);
	T = Delete(99, T);

	PrintTree(T);
	printf("\n");
	printf("%d\n", FindMax(T)->Element);
	printf("%d\n", FindMin(T)->Element);
	printf("%d\n", Find(37, T)->Element);
	return 0;
}
