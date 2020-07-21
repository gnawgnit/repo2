#include <stdio.h>
#include <stdlib.h>
#define MENUSIZE 3
#define MENUSTRSIZE 10
int findsign(char menustr[MENUSIZE ][MENUSTRSIZE ]);
int main(void){
	char menustr[MENUSIZE][MENUSTRSIZE] = {"* 注册", "  登陆", "  退出"};
	int value;
	int ch;
	while(1){
		system("clear");
		for(int i = 0;i<MENUSIZE;i++)
		printf("%s\n", menustr[i]);
		
		//system("stty -echo");
		getchar();
		//system("stty echo");
		
		//找到*号的位置 int value
		value = findsign(menustr);
		//上箭头
		menustr[value][0] = ' ';
		if(ch == 38){
			if(--value == -1)//第一个位置
				value = MENUSIZE - 1;
			menustr[value][0] = '*';
		}
		//下箭头
		else if(ch == 40){
			if(++value == MENUSIZE)//最后一个位置
				value = 0;
			menustr[value][0] = '*';
		}
		//回车键
		else if(ch == 13){
			printf("%d", value);
			return 0;
		}
		//其他
		else
			;
	}
	return 0;
}
int findsign(char menustr[MENUSIZE ][MENUSTRSIZE ]){
	int rev = 0;//默认位置
	while(rev < MENUSIZE){
		if(menustr[rev][0] == '*')
			return rev;
		rev++;
	}
}
