/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月08日13时44分58秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"student.h"
#include<unistd.h>
int main(int argc,char *argv[]) 
{
	LinkList *L; 
	char sno[5] = {'\0'}; 
	char sname[9] = {'\0'}; 
	int b = 1; 
	int i = 1; 
	while (b) 
	{ 
		switch(menue()) 
		{ 
			case 1: 
				L = createTailList(); 
				//L = createHeadList(); 
				break; 
			case 2: 
				//displayAll(L); 
				printf("\t*输入插入哪个位置前："); 
				scanf("%d", &i); 
				insertElem(L, i); 
				//scanf("%s", sno); 
				//insertElemBysno(L, sno); 
				break; 
			case 3: 
				printf("\t*输入待删除学生的学号："); 
			    scanf("%s", sno); 
			    deleteElem(L, sno); 
			    break; 
		   case 4: 
			    printf("*********************************\n"); 
			    printf("*\t学生总数为：%d\t\t*\n", lengthList(L)); 
			    printf("*********************************\n\n"); 
			    break; 
		   case 5: 
			    printf("\t*输入待查找学生的学号："); 
			    scanf("%s", sno); 
			    locateElemBysno(L, sno); 
			    break; 
		   case 6: 
			    printf("\t*输入待查学生的位置："); 
			    scanf("%d", &i); 
			    getElem(L, i); 
			    break; 
		   case 7: 
			    displayAll(L); 
			    break; 
		   case 8: 
			    insertSort(L); 
			    break; 
		   case 9: 
			    i = 2; 
			    while (i) 
			    {      
				    system("clear"); 
				    printf("\n\n\n\n\n\n"); 
				    printf("*********************************\n"); 
				    printf("*\t正在退出(%d秒)\t\t*\n", i--); 
					printf("*********************************\n"); 
  
					sleep(1); 
				} 
			    system("clear"); 
			    return 0; 
			    break; 
		   default: 
			    i = 2; 
			    while (i) 
			    { 
					system("clear"); 
				    printf("**********************************\n"); 
				    printf("*操作数无效，正在返回主菜单(%d秒)*\n", i--); 
				    printf("**********************************\n");   
					sleep(1); 
			    } 
			    break; 
		  } 
		  getchar(); 
		  printf("PRESS ENTER TO CONTINUE!"); 
		  while (1) 
		  { 
			   if ('\n' == getchar()) 
			   { 
				   break; 
			   } 
		  } 
	} 
	return 0; 
} 
