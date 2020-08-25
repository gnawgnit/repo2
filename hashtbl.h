#ifndef _Hashsep_H
#define MinTableSize 20

typedef unsigned int ElementType;
typedef unsigned int Index;

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestoryTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
void Delete(ElementType Key, HashTable H);
ElementType Retrieve(Position P);  //retrieve  找回，检索数据
#endif


struct ListNode{
	ElementType Element;
	struct ListNode *Next; //Position Next;
};

typedef Position List;

struct HashTbl{
	int TableSize;
	List *TheLists;
};
