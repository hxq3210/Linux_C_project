/*************************************************************************
    > 文件名称 : student.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月08日13时45分11秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Student 
{ 
 char sname[9]; 
 char sno[5]; 
 int score; 
}DataType; 
  
typedef struct
{ 
 DataType data; 
 struct Node *next; 
}LinkList; 
  
LinkList * inputdata(); 
  
void display(LinkList * p); 
  
//遍历链表 
void displayAll(LinkList * L); 
  
//插入 
LinkList * createTailList();//尾插 
LinkList * createHeadList();//头插 
  
//查询 
void getElem(LinkList * L, int i);//按序号 
void locateElemBysno(LinkList * L, char ch[]);//按值 
void locateElemBysname(LinkList * L, char ch[]); 
  
int lengthList(LinkList * L); 
  
//插入 
void insertElem(LinkList * L, int i);//在第i个结点前进行插入 
void insertElemBysno(LinkList * L, char ch[5]);//按学号 
  
void deleteElem(LinkList * L, char ch[]); 
  
//排序 
void insertSort(LinkList * L); 
  
int menue(); 
