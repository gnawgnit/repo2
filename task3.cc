//试验3 电话簿管理系统
//链表实现
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <ctype.h>
#include <string>
#include <time.h>           //获取当前时间
#define NAME_SIZE 20
#define NUMBER_SIZE 12
using namespace std;
//链表结构
struct Message{
	char tele_name[NAME_SIZE];
	char tele_number[NUMBER_SIZE];
	char tele_time[64];          //存储时间	
};
//链表节点
typedef struct node{
	node *next;
	Message tele_message;
}Node;

//电话簿类
class Tele_book{
	private:
		Node **linkp;//指向链表节点指针的指针
	public:
		Tele_book(){
			*linkp = NULL;	
		}
		int add_tele();        //添加
		int find_tele();
		int delete_tele();
		void show_tele();
		~Tele_book(){
			Node *current;
			while((current = *linkp) != NULL){
				linkp = &current->next;
				delete current;
			}
		}
};
//增加记录
int Tele_book::add_tele(){

	Node *current_tele;
	Node *new_tele;
	Node **temp_linkp;
	temp_linkp = linkp;        //不能改变linkp指向第一个节点

	//创建新节点
	new_tele = new Node;
	if(new_tele == NULL){//创建失败
		cout<<"内存不足，创建失败\n";
		return false;
	}

	//将指向下一节点位置设为NULL
	new_tele->next = NULL;

	//eatline
	while(getchar()!= '\n')
		continue;

	cout<<"姓名：";
	cin.getline(new_tele->tele_message.tele_name,NAME_SIZE);	
	
	current_tele = *temp_linkp;
	while(current_tele != NULL && strcmp(current_tele->tele_message.tele_name,new_tele->tele_message.tele_name) == -1){
		temp_linkp = &current_tele->next;
		current_tele = *temp_linkp;
	}
	
	//传递值，输入值
	cout<<"电话号码：";
	cin>>new_tele->tele_message.tele_number;
	//当前时间
	time_t time_now = time(0);
	strftime(new_tele->tele_message.tele_time, sizeof(new_tele->tele_message.tele_time),"%Y/%m/%d %X %A",localtime(&time_now));

	new_tele->next = current_tele;
	*temp_linkp = new_tele;

	cout<<"创建成功\n";
	return true;
}
//查找记录
int Tele_book::find_tele(){
	Node *current;
	Node **temp_linkp = linkp;
	current = *temp_linkp;

	cout<<"查找方式：\n";
	cout<<"1.全名查找\n2.名字首字母查找\n0.返回\n";
	cout<<"请选择：";
	char chioce;
	cin>>chioce;
	if(chioce == '1'){
		cout<<"输入全名：";
		char temp_name[NAME_SIZE];
		//eatline
		while(getchar()!= '\n')
			continue;
		cin.getline(temp_name, NAME_SIZE);
		while(current != NULL && strcmp(current->tele_message.tele_name,temp_name) != 0){
			temp_linkp = &current->next;	
			current = *temp_linkp;
		}
		if(current == NULL){
			cout<<"tip:电话簿没有此记录\n\n";
			return false;//失败
		}
		else{
			cout<<"姓名："<<current->tele_message.tele_name<<endl;
			cout<<"电话号码："<<current->tele_message.tele_number<<endl;
			cout<<"存入时间："<<current->tele_message.tele_time<<endl;
			cout<<endl;
			cout<<"按回车键返回系统主页面";
			cout<<endl;
			getchar();
			getchar();
			return true;
		}
	}
	else if(chioce == '2'){
		char ch;
		cout<<"输入首字母：";
		cin>>ch;
		//确保是小写字母
		ch = tolower(ch);
		while(current != NULL){
			if((current->tele_message.tele_name[0]) == ch || current->tele_message.tele_name[0] == ch-32){    //大小写都匹配
				cout<<"姓名："<<current->tele_message.tele_name<<endl;
				cout<<"电话号码："<<current->tele_message.tele_number<<endl;
				cout<<"存入时间："<<current->tele_message.tele_time<<endl;
				cout<<endl;
			}
			temp_linkp = &current->next;
			current = *temp_linkp;
		}
		cout<<"按回车键返回系统主页面";
		cout<<endl;
		getchar();
		getchar();
		return true;


	}
	else
		cout<<"tip:已返回\n\n";
}
//删除记录
int Tele_book::delete_tele(){
	
	cout<<"输入你要删除的电话簿联系人记录的名字：";
	char temp_name[NAME_SIZE];
	cin>>temp_name;
	
	Node *current = *linkp;
	Node *precious = NULL;     //上一节点

		//找到删除值或到链表尾部
	while(current->next != NULL && strcmp(current->tele_message.tele_name, temp_name) != 0){
		precious = current;
		current = current->next;
	}
	//没有找到
	if(current->next == NULL && strcmp(current->tele_message.tele_name, temp_name) != 0){
		cout<<"tip:电话簿无此纪录\n\n";	
		return false;
	}
	else if(strcmp(current->tele_message.tele_name, temp_name) == 0 && precious == NULL){
		*linkp = current->next;
		delete current;
		cout<<"tip:删除成功\n\n";
		return true;
	}
	else{
		precious->next = current->next;	
		delete current;
		cout<<"tip:删除成功\n\n";
		return true;
	}

}
//显示记录
void Tele_book::show_tele(){

	Node *current_tele;
	Node **temp_linkp;
	temp_linkp = linkp;
	current_tele = *temp_linkp;

	while(current_tele != NULL){
		cout<<"姓名："<<current_tele->tele_message.tele_name<<endl;
		cout<<"电话号码："<<current_tele->tele_message.tele_number<<endl;
		cout<<"存入时间："<<current_tele->tele_message.tele_time<<endl;
		cout<<endl;
		temp_linkp = &current_tele->next;
		current_tele = *temp_linkp;
	}
	cout<<"显示完毕\n";
	cout<<"按回车键返回系统主页面\n";
	cout<<endl;
	getchar();
	getchar();
}
//主函数
int main(void){
	Tele_book test;
	while(1){
		system("clear");		//系统清屏指令
		cout<<"欢迎进入电话簿数据系统\n";
		cout<<"1.添加电话簿记录\n2.显示电话簿内容\n";
		cout<<"3.根据姓名查找电话簿数据\n4.根据姓名删除电话簿数据\n";
		cout<<"0.退出系统\n";
		int chioce;
		cout<<"请输入你的选择：";
		cin>>chioce;
		switch(chioce){
			case 1:test.add_tele();break;//添加
			case 2:test.show_tele();break;//显示
			case 3:test.find_tele();break;//查找
			case 4:test.delete_tele();break;//删除
			case 0:system("clear");cout<<"tip:已退出\n";exit(EXIT_SUCCESS);break;
			default:cout<<"tip:无此选项\n\n";
		}

	}
	return 0;
}

