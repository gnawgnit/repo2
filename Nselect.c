//the data and C page 2;find the Nth number;
#include <stdio.h>
#include <stdlib.h>
#define TESTSIZE 20
#include <time.h>
//select the K-th number from number data

void Ksort(int K, int *data){
	int i = 0;
	int j;
	int temp;
	for(i = 0;i<K-1;i++){
		for(j = i+1;j<K;j++){
			if(*(data+j) > *(data+i)){
				temp = *(data+j);
				*(data+j)=*(data+i);
				*(data+i)=temp;
			}
		}
	}
}
void priarr(int K, int *data){
	int i;
	for(i = 0;i<K;i++)
		printf("%d  ", *(data+i));
	printf("\n");
}

void Credata(int K,int *data){
	int i;
	srand((int)time(0));
	for(i = 0;i < K;i++)
		*(data+i) = rand()%100;
}
void Knumber(int K, int *data){
	int *p = (int *)malloc(sizeof(int)*K);
	int i = 0;
	for(;i<K;i++)
		p[i] = data[i];
	Ksort(K, p);
	priarr(K, p);
	int j;
	while(i<TESTSIZE){
		for(j=0;j<K;j++){
			if(*(data+i)>*(p+j)){
				int z = K-1;
				while(z>j){
					*(p+z) = *(p+z-1);
					z--;
				}
				*(p+j) = *(data+i);
				j = K+1;
			}
			else
				;
		}
		i++;
	}
	priarr(K, p);
	printf("%d\n", *(p+K-1));

	free(p);
}
int main(void){
	int data[TESTSIZE];
	Credata(TESTSIZE, data);
	priarr(TESTSIZE, data);
	Knumber(10, data);
	return 0;
}
