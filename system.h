#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//预定义宏
#define FAIL -1
#define SUCC 0
#define PERMIT (6) //允许尝试六次
#define STRSIZE 20
#define MENUSIZE 3
#define MENUSTRSIZE 10
#define BACKSPACE 127   //删除的asccll码值

//函数声明
//登录
int Signup(void);
//功能菜单
int menu(void);
//注册用户
int Register(void);
//验证账户密码
int Authenticate(char *passwdtmp, char *passwd);
//输入账户密码
void Entername(char *name, char *passwd);
void Enterpasswd(char *passwd);

//辅助函数-> 用于接受输入，剔除\n
char *s_fgets(char *val, int n);
//辅助函数 ->用于确定sign*的位置
int findsign(char menustr[MENUSIZE ][MENUSTRSIZE ]);
//判断用户名是否存在
int Authen_name(char *name, char *passwd);//若用户存在，passwd中存储该用户密码以验证，否则为NULL
//函数具体实现
char *s_fgets(char *val, int n){
	char *rev = fgets(val, n, stdin);
	if(rev){
		char ch;
		char *endline = strchr(rev, '\n');
		if(endline)
			*endline = '\0';
		else
			while((ch = getchar())!='\n')
				continue;
	}
	return rev;
}
//打开passwd进行比对
int Authenticate(char *passwdtmp, char *passwd){
	if(strncmp(passwdtmp, passwd, STRSIZE) == 0)
		return SUCC;
	else
		return FAIL;
}
//输入账号密码
void Entername(char *name, char *passwd){
	//system("clear");
	//功能：输入用户名判断是否存在该用户，之后再允许输入密码
	while(1){
		puts("欢迎进入gnawgnit创建的系统");
		puts("请输入您的用户名：");
		s_fgets(name, STRSIZE);
		if(Authen_name(name, passwd) == FAIL){//用户名不存在
			system("clear");
			puts("******************");
			puts("**该用户名不存在**");
			puts("******************\n");
			continue;
			}
		else{
			break;
		}
	}
	return ;
}
/*void Enterpasswd(char *passwd){
	puts("************************");
	puts("**请输入您的用户密码：**");
	puts("************************\n");
	printf("passwd: ");
	//实现不出现明文
	system("stty -echo");
	//while((ch = getchar()) != '\n')
	//	*str++ = ch;
	s_fgets(passwd, STRSIZE);
	system("stty echo");
	return ;
}*/
/*
	不用getch()实现密码的输入，回显为*，最大可输入16位数
*/
//使密码以*号输出
void Enterpasswd(char *pass)
{
	int i=0;
	system("stty -icanon");                   //设置一次性读完操作，即getchar()不用回车也能获取字符
	system("stty -echo");                     //关闭回显，即输入任何字符都不显示
	while(i < STRSIZE)
	{
		pass[i]=getchar();                    //获取键盘的值到数组中
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
	system("stty echo");                    //开启回显
	system("stty icanon");                   //关闭一次性读完操作，即getchar()必须回车也能获取字符
}
int Register(void){
	char passwd[STRSIZE];
	char name[STRSIZE];
	char nametmp[STRSIZE];
	char passwdtmp[STRSIZE];
//打开账户密码文件
	FILE *fp = fopen("passwd", "a+");
	if(!fp){
		puts("Can't Open File");
		exit(EXIT_FAILURE);
	}

	while(1){
		int flag = 0; // 标志，用于判断账户是否相同 0 ->not   1->yes
		fseek(fp,0L,SEEK_SET);//指向文件首数据
		puts("请输入账户名：");
		s_fgets(name,STRSIZE);
		if(strncmp(name,"",STRSIZE) == 0){
			puts("不能是空输入");
			continue;
		}
		else{
			while(fscanf(fp, "%s", nametmp) == 1){
				fscanf(fp, "%s", passwd);//避免讲密码认作用户名
				if(strncmp(name, nametmp,STRSIZE)==0){
					puts("已有相同账户名，重新输入");
					flag = 1;//设置标志为1
					break;
					}
				}
			if(flag == 1)
				continue;//继续输入
			fseek(fp, 0L, SEEK_END);//指向文件尾部
			fprintf(fp, "%s\t", name);
			break;
		}
	}
	while(1){
		puts("请输入账户密码：");
/*
		system("stty -echo");
		s_fgets(passwd,STRSIZE);
		if(strncmp(passwd, "", STRSIZE) ==0 ){
			puts("不能是空输入");
			continue;
			}
		system("stty echo");

		//确认一遍
		puts("请再次输入以确认：");
		system("stty -echo");
		s_fgets(passwdtmp, STRSIZE);
		system("stty echo");
*/
//用另一种输入方式

		Enterpasswd(passwd);
		if(strncmp(passwd, "", STRSIZE) ==0 ){
			puts("不能是空输入");
			continue;
			}
		//确认一遍
		puts("\n请再次输入以确认：");
		Enterpasswd(passwdtmp);


		if(strncmp(passwd, passwdtmp, STRSIZE) == 0){
			fprintf(fp,"%s\n", passwd);
			fclose(fp);//关闭文件
			return SUCC;
			}
		else{
			puts("两次密码不一致，重新输入");
			continue;
			}
	}
}
int Signup(void){
	char name[STRSIZE];
	char passwd[STRSIZE];
	char passwdtmp[STRSIZE];
	int enter_count = 0;  //设置初始输入密码次数
	int pass = FAIL; //判断是否通过,默认为不通过
	system("clear");
	Entername(name, passwd);//通过用户名找到密码
	while(enter_count<PERMIT&&pass == FAIL){
		puts("请输入密码：");
		Enterpasswd(passwdtmp);//用户登录时输入的密码
		pass = Authenticate(passwdtmp, passwd);//比对
		enter_count++;
		system("clear");
		if(pass == FAIL)
			printf("密码错误，你还有%d次尝试机会\n", 6 - enter_count);
	}
	return pass;
}
/*int menu(void){
	int id;//功能id
	puts(" **欢迎进入gnawgnit创建的系统**\n **输入功能号：		     **\n **   1）注册                **\n **   2）登录                **\n **   3）退出                **\n ******************************");
	scanf("%d", &id);
	while(getchar()!='\n')
		continue;
	return id;
}*/
int menu(void){
	char menustr[MENUSIZE][MENUSTRSIZE] = {"* 注册", "  登陆", "  退出"};
	int value;
	int ch;
	while(1){
		system("clear");
		for(int i = 0;i<MENUSIZE;i++)
		printf("%s\n", menustr[i]);
		
		system("stty -icanon");
		system("stty -echo");
		ch = getchar();
		//找到*号的位置 int value
		value = findsign(menustr);
		//上箭头
		if(ch == 'w'){
			menustr[value][0] = ' ';
			if(--value == -1)//第一个位置
				value = MENUSIZE - 1;
			menustr[value][0] = '*';
		}
		//下箭头
		else if(ch == 's'){
			menustr[value][0] = ' ';
			if(++value == MENUSIZE)//最后一个位置
				value = 0;
			menustr[value][0] = '*';
		}
		//回车键
		else if(ch == 'e'){
			system("stty echo");
			system("stty echo");
			return value+1;
		}
		//其他
		else
			;
		system("stty icanon");
		system("stty icanon");
	}
}
int findsign(char menustr[MENUSIZE ][MENUSTRSIZE ]){
	int rev = 0;//默认位置
	while(rev < MENUSIZE){
		if(menustr[rev][0] == '*')
			return rev;
		rev++;
	}
}
int Authen_name(char *name, char *passwd){
	char nametmp[STRSIZE];
	char passwdtmp[STRSIZE];

	FILE *fp = fopen("passwd", "r");
	if(!fp){
		puts("关键文件打不开");
		exit(EXIT_FAILURE);
	}
	while(fscanf(fp, "%s", nametmp)==1){
		if(strncmp(nametmp, name, STRSIZE)==0){
			fscanf(fp, "%s", passwd);
			fclose(fp);
			return SUCC;
		}
		else{
			fscanf(fp, "%s", passwdtmp);
			continue;
		}
	}
	fclose(fp);
	return FAIL;
}
#endif
