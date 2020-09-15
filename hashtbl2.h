#ifndef _HashQuad_H
#define _HashQuad_H

#define MinTableSize 5
typedef int ElementType; 
typedef unsigned int Index;
typedef Index Position;

struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable(int TableSize);
void DestoryTable(HashTable H);
Position Find(ElementType Key, HashTable H);
void Insert(ElementType Key, HashTable H);
ElementType Retrieve(Position P, HashTable H);
HashTable Rehash(HashTable H);	//再散列

#endif
enum KindofEntry{Legitimate, Empty, Delete};
struct HashEntry{
	ElementType Element;
	enum KindofEntry Info;
};
typedef struct HashEntry Cell;

struct HashTbl{
	int TableSize;
	Cell *TheCells;
};
