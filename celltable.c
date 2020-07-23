#include <stdio.h>
#include "system.h"
#define CHECK printf("check\n")
//主函数
int main(void){
	char current_name[NAME_SIZE];
	while(1){
	int id = menu();
	if(id == 1){
		Register();
		system("clear");
		puts("注册成功。请登录");
	}
	else if(id == 2){
		int i = Signup(current_name);
		system("clear");
		if(i == FAIL){
			puts("已锁定");
			exit(EXIT_FAILURE);
		}
		else if(i == NONE){
			puts("还未创建用户，请先注册");
			continue;
		}
		else{
			puts("登录成功。");
			break;
		}
	}
	else if(id == 3){
		puts("已退出");
		exit(EXIT_SUCCESS);
	}
	else {
		system("clear");
		puts("无此功能,已退出");
		continue;
		}
	}
//登录成功
	Node **linkp;
	init(linkp);
	Pre(linkp, current_name);
	while(1){
		int id = menu1();
		if(id == 1){
			add_tele(linkp);
		}
		else if(id == 2){
			show_tele(linkp);
		}
		else if(id == 3){
			find_tele(linkp);
		}
		else if(id == 4){
			delete_tele(linkp);
		}
		else if(id == 5){
			break;
		}
		else
			puts("tip:无此选项\n");
		}
	system("clear");
	puts("tip:已退出\n");
	Lastprin(linkp, current_name);
	delelink(linkp);
	return 0;
}

