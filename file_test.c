#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FAIL -1
#define SUCC 0
#define PERMIT (6) //允许尝试六次
#define STRSIZE 30
void denglu(void);
int menu(void);
int zhuce(void);
char *s_fgets(char *val, int n);
int panduan(char *name, char *passwd);
void shuru(char *name, char *passwd);
int main(void){
	while(1){
	int id = menu();
	if(id == 1){
		zhuce();
		system("clear");
		puts("注册成功。");
	}
	else if(id == 2){
		denglu();
		system("clear");
		puts("登录成功。");
	}
	else if(id == 3){
		exit(1);
	}
	else {
		puts("无此功能,已退出");
		system("clear");
		exit(2);
	}
	}
}
void gongneng(void){
	puts("");
}
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
int panduan(char *name, char *passwd){
	char nametmp[STRSIZE];
	char passwdtmp[STRSIZE];

	FILE *fp = fopen("passwd", "r");
	if(!fp){
		puts("文件打不开");
		exit(EXIT_FAILURE);
	}

	while(fscanf(fp,"%s",nametmp)== 1&&fscanf(fp, "%s", passwdtmp) == 1){
		if(strcmp(nametmp, name) == 0 && strcmp(passwdtmp, passwd) == 0)
		{
			fclose(fp);
			printf("%s\n", name);
			return SUCC;
		}
		else
			continue;
	}
	fclose(fp);
	printf("%s\n", name);
	return FAIL;
}
//输入账号密码
void shuru(char *name, char *passwd){
	//system("clear");
	puts("欢迎进入gnawgnit创建的系统");
	puts("请输入您的用户名：");
	s_fgets(name, STRSIZE);
	puts("请输入您的用户名密码：");
	//实现不出现明文
	char ch;
	char *str = passwd;
	system("stty -echo");
	while((ch = getchar()) != '\n')
		*str++ = ch;
	system("stty echo");
	*str = '\0';
	return ;
}
int zhuce(void){
	char passwd[STRSIZE];
	char name[STRSIZE];
	char nametmp[STRSIZE];
	char passwdtmp[STRSIZE];

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
				if(strncmp(name, nametmp,STRSIZE)==0){
					puts("已有相同账户名，重新输入");
					flag = 1;//设置标志为1
					break;
					}
				}
			if(flag == 1)
				continue;
			fseek(fp, 0L, SEEK_END);//指向文件尾部
			fprintf(fp, "%s\t", name);
			break;
		}
	}
	while(1){
		puts("请输入账户密码：");
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

		if(strncmp(passwd, passwdtmp, STRSIZE) == 0){
			fprintf(fp,"%s\n", passwd);
			fclose(fp);
			return SUCC;
			}
		else{
			puts("两次密码不一致，重新输入");
			continue;
			}
	}
}
void denglu(void){
	char name[STRSIZE];
	char passwd[STRSIZE];
	int i = 0;
	int j = FAIL; //判断是否通过
	system("clear");
	while(i<PERMIT&&j == FAIL){
		shuru(name, passwd);
		j = panduan(name, passwd);
		i++;
		system("clear");
		if(j == FAIL)
			printf("密码错误，你还有%d次尝试机会\n", 6-i);
	}
	if(j == SUCC){
		system("clear");
		printf("密码正确\n");//进入功能区
	}
	else{
		system("clear");
		puts("机会已用完\n");
	}
}
int menu(void){
	int id;
	puts(" **欢迎进入gnawgnit创建的系统**\n **输入功能号：		     **\n **   1）注册                **\n **   2）登录                **\n **   3）退出                **\n ******************************");
	scanf("%d", &id);
	while(getchar()!='\n')
		continue;
	return id;
}
