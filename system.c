#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "system.h"

#define CHECK printf("check\n")
/*------------------------具体函数实现-------------------------------*/
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
/*------------------------登录注册菜单实现-------------------------*/

//打开passwd进行比对
int Authenticate(char *passwdtmp, char *passwd){
	if(passwdtmp != NULL&&strncmp(passwdtmp, passwd, STRSIZE) == 0)//输入不能为空
		return SUCC;
	else
		return FAIL;
}
//输入账号密码
int Entername(char *name, char *passwd){
	//system("clear");
	//功能：输入用户名判断是否存在该用户，之后再允许输入密码
	while(1){
		puts("欢迎进入gnawgnit创建的系统");
		puts("请输入您的用户名：");
		s_fgets(name, STRSIZE);
		int flag;
		if((flag = Authen_name(name, passwd)) == FAIL||flag == NONE){//用户名不存在
			system("clear");
			puts("******************");
			puts("**该用户名不存在**");
			puts("******************\n");
			if(flag == FAIL)
				continue;
			else
				return NONE;
			}
		else{
			break;
		}
	}
	return SUCC;
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
	不用getch()实现密码的输入，回显为*
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
int Signup(char *name){  //name[NAME_SIZE] 主函数传递
	char passwd[STRSIZE];
	char passwdtmp[STRSIZE];
	int enter_count = 0;  //设置初始输入密码次数
	int pass = FAIL; //判断是否通过,默认为不通过
	system("clear");
	if(Entername(name, passwd) == NONE)//没有打开passwd文件
		return NONE;
	else//通过用户名找到密码
		;
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
		for(int i = 0;i<MENUSIZE;i++)
		printf("%s\n", menustr[i]);
		
		system("stty -icanon");
		system("stty -echo");
		ch = getchar();
		//找到*号的位置 int value
		value = findsign(menustr);
		//上箭头
		if(ch == 'w'||ch == '\042'){
			menustr[value][0] = ' ';
			if(--value == -1)//第一个位置
				value = MENUSIZE - 1;
			menustr[value][0] = '*';
			system("clear");
		}
		//下箭头
		else if(ch == 's'||ch == '\041'){
			menustr[value][0] = ' ';
			if(++value == MENUSIZE)//最后一个位置
				value = 0;
			menustr[value][0] = '*';
			system("clear");
		}
		//回车键
		else if(ch == 'e'||ch == '\015'){
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
int findsign(char menustr[MENUSIZE][MENUSTRSIZE]){
	int rev = 0;//默认位置
	while(rev < MENUSIZE){
		if(menustr[rev][0] == '*'){
			return rev;
		}
		rev++;
	}
}
int Authen_name(char *name, char *passwd){
	char nametmp[STRSIZE];
	char passwdtmp[STRSIZE];

	FILE *fp = fopen("passwd", "r");
	if(!fp){
		puts("请先创建账号");
		return NONE;
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
/*--------------------------------------------------------------*/


/*------------------------链表实现电话簿-------------------------*/

//初始化链表指针
void init(Node **linkp){
	*linkp = NULL;
}
void delelink(Node **linkp){
	Node *current;
	while((current = *linkp)!=NULL){
		//linkp = &current->next;要访问NULL的地址
		*linkp = current->next;
		free(current);
	}
}
//增加记录
int add_tele(Node **linkp){
	Node *current_tele;
	Node *new_tele;
	Node **temp_linkp;
	temp_linkp = linkp;        //不能改变linkp指向第一个节点

	//创建新节点
	//new_tele = new Node;
	new_tele = malloc(sizeof(struct node));
	if(new_tele == NULL){//创建失败
		puts("内存不足，创建失败");
		return false;
	}

	//将指向下一节点位置设为NULL
	new_tele->next = NULL;
	
	printf("\n姓名："); //用换行符以打印该行
	s_fgets(new_tele->tele_message.tele_name, NAME_SIZE);
	
	current_tele = *temp_linkp;
	while(current_tele != NULL && strcmp(current_tele->tele_message.tele_name, new_tele->tele_message.tele_name) == -1){
		temp_linkp = &current_tele->next;
		current_tele = *temp_linkp;
	}
	//传递值，输入值
	printf("电话号码：");
	s_fgets(new_tele->tele_message.tele_number, NUMBER_SIZE);
	//当前时间
	time_t time_now = time(0);
	strftime(new_tele->tele_message.tele_time, sizeof(new_tele->tele_message.tele_time),"%Y/%m/%d %X %A",localtime(&time_now));

	new_tele->next = current_tele;
	*temp_linkp = new_tele;

	puts("创建成功");
	return true;
}
//查找记录
int find_tele(Node **linkp){
	Node *current;
	Node **temp_linkp = linkp;
	current = *temp_linkp;

	puts("查找方式：");
	//menu()
	//puts("1.全名查找\n2.名字首字母查找\n0.返回");
	int id = menu2();
	if(id == 1){
		printf("输入全名：");
		char temp_name[NAME_SIZE];
		s_fgets(temp_name, NAME_SIZE);
		while(current != NULL && strcmp(current->tele_message.tele_name,temp_name) != 0){
			temp_linkp = &current->next;
			current = *temp_linkp;
		}
		if(current == NULL){
			puts("tip:电话簿没有此记录");
			return false;//失败
		}
		else{
			system("clear");
			printf("姓名：%s\n", current->tele_message.tele_name);
			printf("电话号码：%s\n", current->tele_message.tele_number);
			printf("存入时间：%s\n", current->tele_message.tele_time);
			puts("按回车键返回系统主页面");
			getchar();
			return true;
		}
	}
	else if(id == 2){
		char ch;
		printf("输入首字母：");
		ch = getchar();
		while(getchar()!='\n')
			continue;
		//确保是小写字母
		ch = tolower(ch);
		while(current != NULL){
			if((current->tele_message.tele_name[0]) == ch || current->tele_message.tele_name[0] == ch-32){    //大小写都匹配
				system("clear");
				printf("姓名：%s\n", current->tele_message.tele_name);
				printf("电话号码：%s\n", current->tele_message.tele_number);
				printf("存入时间：%s\n", current->tele_message.tele_time);
			}
			temp_linkp = &current->next;
			current = *temp_linkp;
		}
		puts("按回车键返回系统主页面");
		getchar();
		return true;


	}
	else
		puts("tip:已返回\n");
}
//删除记录
int delete_tele(Node **linkp){
	printf("输入你要删除的电话簿联系人记录的名字：");
	char temp_name[NAME_SIZE];
	s_fgets(temp_name, NAME_SIZE);
	
	Node *current = *linkp;
	Node *precious = NULL;     //上一节点

		//找到删除值或到链表尾部
	while(current->next != NULL && strcmp(current->tele_message.tele_name, temp_name) != 0){
		precious = current;
		current = current->next;
	}
	//没有找到
	if(current->next == NULL && strcmp(current->tele_message.tele_name, temp_name) != 0){
		puts("tip:电话簿无此纪录\n");
		return false;
	}
	//
	else if(strcmp(current->tele_message.tele_name, temp_name) == 0 && precious == NULL){
		*linkp = current->next;
		free(current);
		puts("tip:删除成功\n");
		return true;
	}
	else{
		precious->next = current->next;	
		free(current);
		puts("tip:删除成功\n");
		return true;
	}
}
//显示记录
void show_tele(Node **linkp){
	Node *current_tele;
	Node **temp_linkp;
	temp_linkp = linkp;
	current_tele = *temp_linkp;

	while(current_tele != NULL){
		printf("姓名：%s\n", current_tele->tele_message.tele_name);
		printf("电话号码：%s\n", current_tele->tele_message.tele_number);
		printf("存入时间：%s\n", current_tele->tele_message.tele_time);

		temp_linkp = &current_tele->next;
		current_tele = *temp_linkp;
	}
	puts("显示完毕");
	puts("按回车键返回系统主页面");
	getchar();
	getchar();
}

/*--------------------------------------------------------------*/
int menu1(void){
	char menustr[MENUSIZE1][MENUSTRSIZE1]={"* 添加电话簿记录","  显示电话簿内容", "  根据姓名查找电话簿数据","  根据姓名删除电话簿数据","  退出系统"};
	int value;
	int ch;
		while(1){
		system("clear");
		puts("欢迎进入电话簿数据系统");
		for(int i = 0;i<MENUSIZE1;i++)
			printf("%s\n", menustr[i]);
		system("stty -icanon");
		system("stty -echo");
		ch = getchar();
		//找到*号的位置 int value
		value = findsign1(menustr);
		//上箭头
		if(ch == 'w'){
			menustr[value][0] = ' ';
			if(--value == -1)//第一个位置
				value = MENUSIZE1 - 1;
			menustr[value][0] = '*';
		}
		//下箭头
		else if(ch == 's'){
			menustr[value][0] = ' ';
			if(++value == MENUSIZE1)//最后一个位置
				value = 0;
			menustr[value][0] = '*';
		}
		//回车键
		else if(ch == 'e'){
			system("stty icanon");
			system("stty echo");
			return value+1;
		}
		//其他
		else
			;
		system("stty icanon");
		system("stty echo");
	}
}
int findsign1(char menustr[MENUSIZE1][MENUSTRSIZE1]){
	int rev = 0;//默认位置
	while(rev < MENUSIZE1){
		if(menustr[rev][0] == '*'){
			return rev;
		}
		rev++;
	}
}
int menu2(void){
	//puts("1.全名查找\n2.名字首字母查找\n0.返回");
	char menustr[MENUSIZE2][MENUSTRSIZE2]={"* 全名查找", "  名字首字母查找", "  返回"};
	int value;
	int ch;
		while(1){
		system("clear");
		for(int i = 0;i<MENUSIZE2;i++)
			printf("%s\n", menustr[i]);
		system("stty -icanon");
		system("stty -echo");
		ch = getchar();
		//找到*号的位置 int value
		value = findsign2(menustr);
		//上箭头
		if(ch == 'w'){
			menustr[value][0] = ' ';
			if(--value == -1)//第一个位置
				value = MENUSIZE2 - 1;
			menustr[value][0] = '*';
		}
		//下箭头
		else if(ch == 's'){
			menustr[value][0] = ' ';
			if(++value == MENUSIZE2)//最后一个位置
				value = 0;
			menustr[value][0] = '*';
		}
		//回车键
		else if(ch == 'e'){
			system("stty icanon");
			system("stty echo");
			return value+1;
		}
		//其他
		else
			;
		system("stty icanon");
		system("stty echo");
	}
}
int findsign2(char menustr[MENUSIZE2][MENUSTRSIZE2]){
	int rev = 0;//默认位置
	while(rev < MENUSIZE2){
		if(menustr[rev][0] == '*'){
			return rev;
		}
		rev++;
	}
}
/*----------------------------------------------------------------------*/
//打开文件，读取内容到链表
//形成数据文件名

int Pre(Node **linkp, char *name){

	char filename[NAME_SIZE];
	strncpy(filename, name, NAME_SIZE);
	filename[NAME_SIZE-4] = '\0';
	strcat(filename, ".da");

	FILE *fp = fopen(filename, "r");//以读模式打开
	if(!fp){
		return 0;  //没有文件
	}
	char namecell[NAME_SIZE];
	char numbercell[NUMBER_SIZE];
	char timecell[64];
	while((fscanf(fp, "%s", namecell) == 1) && (fscanf(fp, "%s", numbercell)==1)&&(fscanf(fp, "%s", timecell) == 1)){
		//printf("%s %s %s\n", namecell, numbercell, timecell);
		preadd_tele(linkp, namecell, numbercell, timecell);
	}
	fclose(fp);
	if(!fp)
		exit(EXIT_FAILURE);
	return 0;
}
int preadd_tele(Node **linkp, char *namecell, char *numbercell, char *timecell){
	Node *current_tele;
	Node *new_tele;
	Node **temp_linkp;
	temp_linkp = linkp;        //不能改变linkp指向第一个节点

	//创建新节点
	//new_tele = new Node;
	new_tele = malloc(sizeof(struct node));
	if(new_tele == NULL){//创建失败
		puts("内存不足，创建失败");
		return false;
	}

	//将指向下一节点位置设为NULL
	new_tele->next = NULL;
	
	strncpy(new_tele->tele_message.tele_name, namecell, NAME_SIZE);
	printf("hello\n");
	current_tele = *temp_linkp;
	while(current_tele != NULL && strcmp(current_tele->tele_message.tele_name, new_tele->tele_message.tele_name) == -1){
		temp_linkp = &current_tele->next;
		current_tele = *temp_linkp;
	}
	//传递值，输入值
	strncpy(new_tele->tele_message.tele_number, numbercell, NUMBER_SIZE);
	strncpy(new_tele->tele_message.tele_time, timecell, 64);

	new_tele->next = current_tele;
	*temp_linkp = new_tele;
	return true;
}
int Lastprin(Node **linkp, char *name){
	char filename[NAME_SIZE];
	strncpy(filename, name, NAME_SIZE);
	filename[NAME_SIZE-4] = '\0';
	strcat(filename, ".da");

	FILE *fp = fopen(filename, "w");//以写模式打开
	if(!fp){
		return false;  //没有文件
	}

	Node *current_tele;
	Node **temp_linkp;
	temp_linkp = linkp;

	while((current_tele = *temp_linkp) != NULL){
		fprintf(fp, "%s\t", current_tele->tele_message.tele_name);
		fprintf(fp, "%s\t", current_tele->tele_message.tele_number);
		fprintf(fp, "%s\n", current_tele->tele_message.tele_time);
		*temp_linkp = current_tele->next;
	}
	fclose(fp);
	return true;
}
