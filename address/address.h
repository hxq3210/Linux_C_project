/*************************************************************************
    > 文件名称 : address.h
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月12日14时53分16秒
    > 描   述  : 
 ************************************************************************/
#include <stdio.h> 
#include <malloc.h> //得到指向大小为Size的内存区域的首字节的指针// 
#include <string.h> 
#include <stdlib.h> //标准库函数//  
#define NULL 0 
#define LEN sizeof(struct address_list) //计算字节// 
int n; 
struct address_list 
{ 
  char name[30];   //名字 
  char work[30];   //职业 
  char handset[30]; //手机 
  char email[30];  //电子邮件 
  char address[30]; //通讯地址 
  struct address_list *next; 
}; 
struct address_list *shifang(struct address_list *head); // 释放内存函数声明 
//创建函数，不带头结点的链表 
struct address_list *creat(void);
//输出函数 
void print(struct address_list *head);   
//增加函数 
struct address_list *insert(struct address_list *head);  
//删除函数
struct address_list* delete_txl(struct address_list *head); 
//显示函数 
struct address_list *display(struct address_list *head); 
//排序函数 
struct address_list *paixu(struct address_list *head);
//姓名查找函数 
struct address_list *search(struct address_list *head);
//释放内存函数 
struct address_list *shifang(struct address_list *head);
//文件写入函数 
void save(struct address_list *head);
//文件读出函数 
struct address_list *load(struct address_list *head);
//综合操作函数 
struct address_list *menu(struct address_list *head);

















