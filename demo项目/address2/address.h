/*************************************************************************
    > 文件名称 : address.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日20时02分16秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
//#include<unistd.h>
typedef struct info
{
	char name[15];  //姓名
	char city[10];  //城市
	char province[10];  //省
	char tel[15];	//电话
};
typedef struct node   //定义通讯录链表的结构体
{
	struct info data;
	struct node *next;
}Node, *link;
//检测字符串
void stringinput(char *t,int lens,char *notice);
//输入通讯录信息
void enter(link l); //输入记录
//删除
void del(link l);
//查询
void search(link l);
//显示
void list(link l);
//保存
void save(link l);
//将磁盘文件中的内容读入通讯录链表
void load(link l);
//初始化菜单界面
menu_select();

