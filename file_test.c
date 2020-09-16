#include <stdio.h>
#define STRSIZE 10
void Enterpasswd(char *pass)
{
	int i=0;
	//system("stty -icanon");                   //设置一次性读完操作，即getchar()不用回车也能获取字符
	//system("stty -echo");                     //关闭回显，即输入任何字符都不显示
	while(i < STRSIZE)
	{
		pass[i]=getche();                    //获取键盘的值到数组中
		if(i == 0 && pass[i] == BACKSPACE)
		{
			i=0;                              //若开始没有值，输入删除，则，不算值
			pass[i]='\0';
			continue;
		}
		else if(pass[i] == BACKSPACE)
		{
			printf("\b \b");                    //若删除，则光标前移，输空格覆盖，再光标前移
			pass[i]='\0';
			i=i-1;                              //返回到前一个值继续输入
			continue;                           //结束当前循环
		}
		else if(pass[i] == '\n')               //若按回车则，输入结束
		{
			pass[i]='\0';
			break;
		}
		else
		{
			printf("*");
		}
		i++;
	}
	//system("stty echo");                    //开启回显
	//system("stty icanon");                   //关闭一次性读完操作，即getchar()必须回车也能获取字符
}
int main(void){
	char name[STRSIZE];
	Enterpasswd(name);
	printf("%s/n", name);
	return 0;
}