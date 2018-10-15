/*************************************************************************
    > 文件名称 : address.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日20时02分13秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"address.h"
void stringinput(char *t,int lens,char *notice)
{
	char n[50];
	do
	{
		printf(notice);   
		scanf("%s",n);
		if(strlen(n)>lens)
			printf("\n 输入有误!请重新输入!\n");
	}
	while(strlen(n)>lens);
	strcpy(t,n);	//将输入字符串拷贝到字符串t中
}
/*输入通讯录信息*/
void enter(link l)
{
	Node *p ,*q;
	q = l;
	while(1)
	{
		p = (Node*)malloc(sizeof(Node));  //申请节点空间
		if(!p)			
		/*未申请成功提示信息*/
		{
			printf("保存失败\n");
			return ;
		}
		stringinput(p->data.name,15,"请输入姓名(输入*0*退出):");
		/*检测姓名输入是否正确*/
		if(strcmp(p->data.name,"0")==0)
			break;
		stringinput(p->data.city,10,"请输入所在城市:");
		stringinput(p->data.tel,15,"请输入电话号码:");
		p->next = NULL;
		q->next = p;
		q = p;
	}
}
/*删除指定记录*/
void del(link l)
{
	Node *p,*q;
	char s[20];
	q = l;
	p = q->next;
	printf("请输入姓名:");
	scanf("%s",s);    //输入要删除人的姓名
	while(p)
	{
		if(strcmp(s,p->data.name)==0)
		{
			q->next = p->next;  //删除p节点
			free(p);
			printf("删除成功!\n");
			break;
		}
		else
		{
			q = p;
			p = q->next;
		}
	}
	getchar();
}
/*查询指定记录*/
void search(link l)
{
	char name[20];
	Node *p;
	p = l->next;
	printf("请输入要查询的姓名:");
	scanf("%s",name);
	while(p)
	{
		if(strcmp(p->data.name,name)==0)
		{
			printf("%s\n",p->data);
//			getchar();
			break;
		}
		else
			p = p->next;
	}
}
/*
void display(link l)
{
	Node *p;
	p = l->next;
	while(p!=NULL)
	{
		printf("\t%s\t%s\t%s\n",p->data.name,p->data.city,p->data.tel);
	}

}
*/
/*显示所有存储记录*/
void list(link l)
{
	Node *p;
	p = l->next;
	while(p!=NULL)
		//遍历链表
	{
//		printf("%s",p->data);
		printf("\t%s\t%s\t%s\n",p->data.name,p->data.city,p->data.tel);
//		display(p);
		p = p->next;
	}
	getchar();
}
/*保存输入的通讯录信息*/
void save(link l)
{
	Node *p;
	FILE *fp;
	p = l->next;
	if((fp = fopen("~/Desktop/list","wb"))==NULL)
	{
		printf("打开失败!\n");
		exit(1);
	}
	printf("保存信息\n");
	while(p)
		//将节点写入磁盘文件
		{
			fwrite(p,sizeof(Node),l,fp);
			p = p->next;
		}
	fclose(fp);
	getchar();
}
//将磁盘内容读入到通讯录链表
void load(link l)
{
	Node *p,*r;
	FILE *fp;
	l->next = NULL;
	r = l;
	if((fp = fopen("~/Desktop/list","rb"))==NULL)
	{
		printf("打开失败\n");
		exit(1);
	}
	printf("保存信息\n");
	while(!feof(fp))
	{
		p = (Node*)malloc(sizeof(Node));//申请节点空间
		if(!p)
		{
			printf("申请内存失败!");
			return;
		}
		if(fread(p,sizeof(Node),l,fp)!=1)
			break;
		else
		{
			p->next = NULL;
			r->next = p; //插入链表中
			r = p;
		}
	}
	fclose(fp);
	getchar();
}
//初始化菜单
menu_select()
{
	int i;
	printf("\n\n");
	printf("\t****************通讯录****************\n");
	printf("\t|* 1.输入联系人       2.删除联系人  *|\n");
	printf("\t|* 3.联系人清单       4.查询联系人  *|\n");
	printf("\t|* 5.  退出                         *|\n");
	printf("\t**************************************\n");
	do
	{
		printf("\n\t请输入选项:");
		scanf("%d",&i);
	}while(i<0||i>5);
	return i;
}


