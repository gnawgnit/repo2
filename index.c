#include <stdio.h>
#include "system.h"

int main(void){
	while(1){
	int id = menu();
	if(id == 1){
		Register();
		system("clear");
		puts("注册成功。");
	}
	else if(id == 2){
		int i = Signup();
		system("clear");
		if(i == FAIL)
			puts("已锁定");
		else
			puts("登录成功。");
	}
	else if(id == 3){
		exit(1);
	}
	else {
		system("clear");
		puts("无此功能,已退出");
		exit(2);
	}
	}
}

