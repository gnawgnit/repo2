#ifndef _Tree_H

typedef int ElementType;
struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElementType X, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElementType X, SearchTree T);
SearchTree Delete(ElementType X, SearchTree T);
ElementType Retrieve(Position P); //检索数据

#endif

struct TreeNode{
	ElementType Element;
	SearchTree Left;
	SearchTree Right;
};
void Error(char *str){
	printf("%s\n", str);
}

