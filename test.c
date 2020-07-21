#include <stdio.h>
#include <stdlib.h>
int main(void){
	FILE *fp = fopen("~/test.txt", "r");
	if(!fp){
		exit(1);
		puts("cann't open this file");
	}
	FILE *fp2 = fopen("~/test1.txt", "w");
	if(!fp2){
		exit(1);
		puts("cann't open this file");
	}
	char ch;
	while(ch = getc(fp)!= EOF){
		putc(ch, stdout);
	}
	fclose(fp);
	fclose(fp2);
	if(!fp||!fp2)
		puts("cann't close the files");
	puts("cann't close the files");
	return 0;
}
