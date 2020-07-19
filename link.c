//链表实现栈的Push和Pop
//2020 7 12 
#include <stdio.h>
#include <stdlib.h>
#define NAMESIZE 20
#include <string.h>
typedef struct {
	int id;
	char name[NAMESIZE];
}Data;
typedef struct link{
	Data Link_val;
	struct link* Next;
}Link;

Data Default = {
	0,
	"no data"
};
Data rev;
Link head = {
	{
		0,
		"no data"
	},
	NULL
};
//Push
int Push(Data value){
	Link *ptr_val = malloc(sizeof(struct link));
	if(!ptr_val){
		exit(EXIT_FAILURE);
		printf("memory is full!");
	}
	ptr_val->Next = NULL;
	ptr_val->Link_val.id = value.id;
	strcpy(ptr_val->Link_val.name, value.name);
	
	Link *Pre = &head;
	while(Pre->Next != NULL){
		Pre = Pre -> Next;
	}

	Pre->Next = ptr_val;
	return 1;

}
//Pop
Data *Pop(void){
	Link *Pre = &head;
	Link *Cur = NULL;

	while(Pre->Next != NULL){
		Cur = Pre;
		Pre = Pre->Next;
	}
	if(Cur == NULL)
		return &Default;
	Data *Ptr_val = &rev;
	Ptr_val->id = Pre->Link_val.id;
	strcpy(Ptr_val->name, Pre->Link_val.name);

	Cur->Next = NULL;
	free(Pre);
	return Ptr_val;
}
void Print(Data *value){
	printf("数据如下：\n");
	printf("%d\t%s\n", value->id, value->name);
	return ;
}
int main(void){
	Data val1 = {
		520,
		"wangting"
	};
	Data val2 = {
		1314,
		"dingweiwei"
	};
	Data val3 = {
		250,
		"gnawgnit"
	};

	int test = Push(val1);
	Push(val3);
	Push(val2);

	printf("%d\n", test);

	Print(Pop());
	Print(Pop());
	Print(Pop());
	Print(Pop());
	Print(Pop());


	return 0;
}
