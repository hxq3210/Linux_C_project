/*************************************************************************
    > 文件名称 : linklist.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月01日09时00分56秒
    > 描   述  : 
 ************************************************************************/
typedef int ElemType;
typedef struct info
{
	char name[15];  //姓名
	char city[10];  //城市
	char province[10];  //省
	char tel[15];	//电话
}; 
/*
*链表通用类型
*ElemType 代表自定义的数据类型 
*struct Node *next 代表 结构体指针（指向下一个结构体，完成链表动作） 
*/
typedef struct Node
{
	 ElemType data;
	 struct Node *next;
}Node, *link; 
void initList(Node **pNode);
Node *create(Node *pHead);
void printList(Node *pHead);
void insert_data(Node **pNode,int i);
void delete_data(Node **pNode,int i);
int search_data(Node *pNode,int elem);
int linklist_del(Node *pNode,int elem);
void linklist_free(Node *pNode);
void linklist_free2(Node *pNode);
menu_select();








