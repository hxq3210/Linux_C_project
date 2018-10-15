/*************************************************************************
    > 文件名称 : linklist.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月01日09时00分52秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef int ElemType;
 
/**
*链表通用类型
*ElemType 代表自定义的数据类型 
*struct Node *next 代表 结构体指针（指向下一个结构体，完成链表动作） 
*/
typedef struct Node
{
	 ElemType data;
	 struct Node *next;
}Node; 
 
/*==========单链表的初始化================*/
/*
*头结点指针数据域设置为空 
*/
void initList(Node **pNode)
{
	 *pNode=NULL;
}
/*===========单链表的创建=================*/
/*
*功能实现：通过用户不断输入数据，创建链表
*利用游标俩个指针（p1,p2），将申请下的数据块(存入用户输入数据)，链接起来 
*/
Node *create(Node *pHead)
{
	 Node *p1;
	 Node *p2;
	 p1=p2=(Node *)malloc(sizeof(Node));     //申请内存空间 
	 memset(p1,0,sizeof(Node));       //存入数据域清空 
	 printf("请输入节点值 -1 结束\n");
	 scanf("%d",&p1->data);
	 p1->next=NULL;          
	 while(p1->data>0)
	 {         //输入负数结束   
		 if(pHead==NULL)
		   pHead=p1;
		 else
			 p2->next=p1;	
		 p2=p1;
		 p1=(Node *)malloc(sizeof(Node));
		 memset(p1,0,sizeof(Node));
	     scanf("%d",&p1->data);
	     p1->next=NULL;
	 }
	 return pHead;
}
/*=================链表的遍历==================*/
/**
*从头结点开始，不断遍历出数据域的内容将表遍历 
*/
void printList(Node *pHead)
{
	if(NULL==pHead)
    printf("链表为空\n");
	 else
	 {
		 while(pHead!=NULL)
		 {
			  printf("%d ",pHead->data);
			  pHead=pHead->next;
		 }
     } 
	 printf("\n");
} 
/*===============插入节点==================*/
/**
*Node **pNode 传入头结点空间地址
*int i 传入要插入的结点位置 
*/
void insert_data(Node **pNode,int i)
{
	 Node *temp;
	 Node *target;
	 Node *p;
	 int item;
	 int j=1;
	 printf("输入要插入的节点值:");
	 scanf("%d",&item);
	 target=*pNode;             
	 for(;j<i-1;target=target->next,j++); //不断移动target位置，到要插入结点位置， 
	 temp=(Node *)malloc(sizeof(Node));   //申请内存空间 
	 temp->data=item;       //存入要存入的数据位置 
	 p=target->next;        
	 target->next=temp;
	 temp->next=p; 	
} 
/*===============删除节点====================*/
/**
*删除结点后，释放内存空间free(temp) 
*/
void delete_data(Node **pNode,int i)
{
	 Node *target;
	 Node *temp;
	 int j=1;
	 target=*pNode;
	 for(;j<i-1 && target->next!=NULL;++j)
			target=target->next;
	 if(i<0&&target->next!=NULL)
	 {
		 temp=target->next;
		 target->next=temp->next;
		 free(temp);
	 }
}
/*===============查找结点====================*/
int search_data(Node *pNode,int elem)
{
	 Node *target;
	 int i=1;
	 for(target=pNode;target->data!=elem && target->next!=NULL;++i,target=target->next);
	 if(target->next==NULL)
		 return 0;
	 else
	     return i;
}

/*=================单链表删除=================*/
int linklist_del(Node *pNode,int elem)
{
	Node *p1 = pNode;
	Node *p2 = p1->next;
	while(p2!=NULL)
	{
		if(p2->data == elem)
		{
			p1->next = p2->next;
			free(p2);
			p2=p1->next;
		}
		else
		{
			p1=p1->next;
			p2=p2->next;
		}
	}
	return 0;
}


/*=================单链表释放=================*/
void linklist_free(Node *pNode)
{
	Node * p = NULL;
	while(pNode)
	{
		p=pNode;
		pNode=pNode->next;
		free(p);
	}
	pNode=NULL;
}
void linklist_free2(Node *pNode)
{
	Node *p1 = pNode;
	Node *p2 = pNode->next;
	while(p2!=NULL)
	{
		p1->next = p2->next;
		free(p2);
		p2 = p1->next;
	}
	free(p1);
	p1=NULL;
	p2=NULL;
//	return 0;
}
//初始化菜单
menu_select()
{
	int i;
	printf("\n\n");
	printf("\t****************通讯录****************\n");
	printf("\t|* 1.输入联系人       2.删除联系人  *|\n");
	printf("\t|* 3.联系人清单       4.查询联系人  *|\n");
	printf("\t|* 5.修改联系人       6.保存联系人  *|\n");
	printf("\t|* 7.   退出                       *|\n");
	printf("\t**************************************\n");
	do
	{
		printf("\n\t请输入选项:");
		scanf("%d",&i);
	}while(i<0||i>7);
	return i;
}
