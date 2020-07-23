#ifndef _SYSTEM_H
#define _SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>           //获取当前时间

//预定义宏
//页面功能菜单
/*-------------------------*/
#define FAIL -1
#define NONE 1     //没有用户
#define SUCC 0
#define PERMIT (6) //允许尝试六次
#define STRSIZE 20
#define MENUSTRSIZE 10  //登录页面
#define MENUSIZE 3
#define MENUSTRSIZE1 45  //功能页面
#define MENUSIZE1 5
#define MENUSTRSIZE2 40  //查找页面
#define MENUSIZE2 3
#define BACKSPACE 127   //删除的asccll码值
/*-------------------------*/

//电话簿管理系统
/*-------------------------*/
#define false 0
#define true 1
#define NAME_SIZE 20
#define NUMBER_SIZE 12
/*-------------------------*/

//链表结构
/*-------------------------*/
typedef struct message{
	char tele_name[NAME_SIZE];
	char tele_number[NUMBER_SIZE];
	char tele_time[64];          //存储时间	
}Message;
//链表节点
typedef struct node{
	struct node *next;
	Message tele_message;
}Node;
/*-------------------------*/

//函数声明
/*----------------------------------------------*/
/*-----------------页面---------------*/
//登录
int Signup(char *name);
//注册用户
int Register(void);
//验证账户密码
int Authenticate(char *passwdtmp, char *passwd);
//输入账户密码
int Entername(char *name, char *passwd);
void Enterpasswd(char *passwd);

//判断用户名是否存在
int Authen_name(char *name, char *passwd);//若用户存在，passwd中存储该用户密码以验证，否则为NULL
/*-------------------------*/


/*-----------------结构---------------*/
//初始化链表指针
void init(Node **linkp);
//释放内存
void delelink(Node **linkp);
//增加记录
int add_tele(Node **linkp);
//查找记录
int find_tele(Node **linkp);
//删除记录
int delete_tele(Node **linkp);
//显示记录
void show_tele(Node **linkp);

/*---------------------------*/


/*-------------------辅助函数------------*/



//辅助函数-> 用于接受输入，剔除\n
char *s_fgets(char *val, int n);

//输出菜单
int menu(void);
int menu1(void);
int menu2(void);

//辅助函数 ->用于确定sign*的位置
int findsign(char menustr[MENUSIZE][MENUSTRSIZE]);
int findsign1(char menustr[MENUSIZE1][MENUSTRSIZE1]);
int findsign2(char menustr[MENUSIZE2][MENUSTRSIZE2]);
/*----------------------------------*/
int Pre(Node **linkp, char *name);
int preadd_tele(Node **linkp, char *namecell, char *numbercell, char *timecell);
int Lastprin(Node **linkp, char *name);
#endif
