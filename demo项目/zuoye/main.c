/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月01日09时00分37秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linklist.h"
int main(int argc, char *argv[])
{

	 int i,j;
	 Node *pHead=NULL;
	 initList(&pHead);
	 pHead=create(pHead);
	 printList(pHead);
	 printf("输入插入节点位置\n");
	 scanf("%d",&i);
	 insert_data(&pHead,i);
	 printList(pHead);
	 for(j=0;j<pHead;j++)
	 {
		printf("输入删除节点值\n");
		 scanf("%d",&i);
		 linklist_del(pHead,i);
		 printList(pHead);
	 }
//	 printf("输入查找节点\n");
//	 scanf("%d",&i);
//	 printf("节点所在位置：%d\n",search_data(pHead,i));
	 linklist_free(pHead);
	 return 0;

}
