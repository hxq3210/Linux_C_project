/*************************************************************************
    > 文件名称 : student.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月08日13时45分06秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"student.h"
int menue() 
{ 
	system("clear"); //警告音 
//	printf("\033[0m");    //关闭所有属性 
  
// printf("\033[44;37m");   //47是字背景颜色,33是字体的颜色 
// printf ("\033[5m");    //闪烁 
 printf("\n^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^\n\n"); 
// printf("\033[0m");    //关闭所有属性 
   
// printf("\033[44;37m"); 
 printf("╭═══════════════════════════════╮\n"); 
 printf("║\t学生成绩管理程序\t║\n"); 
 printf("║\t\t\t\t║\n"); 
 printf("║\t<1>创建\t\t\t║\n"); 
 printf("║\t<2>指定位置后插入\t║\n"); 
 printf("║\t<3>按位置删除\t\t║\n"); 
 printf("║\t<4>求学生总数\t\t║\n"); 
 printf("║\t<5>按学号查找\t\t║\n"); 
 printf("║\t<6>按位置查找\t\t║\n"); 
 printf("║\t<7>显示所有学生\t\t║\n"); 
 printf("║\t<8>成绩排序\t\t║\n"); 
 printf("║\t<9>退出\t\t\t║\n"); 
 printf("╰═══════════════════════════════╯\n\n"); 
  
// printf ("\033[5m"); 
 printf("^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^ ^_^\n\n"); 
// printf("\033[0m");    //关闭所有属性 
/*
 time_t rawtime; 
 struct tm * timeinfo; 
 time ( &rawtime ); 
 timeinfo = localtime ( &rawtime ); 
 //printf ( "\t\007%s", asctime (timeinfo) ); 
   
 printf ("\033[;34m"); 
 printf ("\t[%4d-%02d-%02d %02d:%02d:%02d]\n", 
   1900+timeinfo->tm_year, 
//  1+timeinfo->tm_mon, 
//   timeinfo->tm_mday, 
//   timeinfo->tm_hour, 
//   timeinfo->tm_min, 
//   timeinfo->tm_sec); 
   
// char colorname[3][20] = {{"RED"}, {"BLUE"}, {"YELLLOW"}}; 
// srand(time(&rawtime)); //时间触发    
 printf("\t输入功能项：");
 */
 int a = 0; 
 scanf("%d",&a); 
 printf("\033[0m");  
 system("clear"); 
 return a; 
} 
  
LinkList * inputdata() 
{ 
 LinkList *s = NULL; 
 char sno[5] = {'\0'}; 
 char sname[9] = {'\0'}; 
 int score = 0; 
   
 printf("\tsno\t->"); 
 scanf("%s", sno); 
 if (sno[0] == '#') { 
  return s; 
 } 
 s = (LinkList *)malloc(sizeof(LinkList)); 
 strcpy(s -> data.sno, sno); 
   
 printf("\tsname\t->"); 
 scanf("%s", sname); 
 strcpy(s -> data.sname, sname); 
   
 printf("\tscore\t->"); 
 scanf("%d", &score); 
 s -> data.score = score; 
   
 printf("\n"); 
 return s; 
} 
  
void display(LinkList * p) 
{ 
printf("╭═══════════════════════════════════════════════╮\n"); 
printf("║\tsno\t\tsname\t\tscore\t║\n"); 
printf("║\t%s\t\t%s\t\t%-4d\t║\n", p->data.sno, p->data.sname, p->data.score); 
printf("╰═══════════════════════════════════════════════╯\n\n");} 
void displayAll(LinkList * L) 
{ 
printf("╭═══════════════════════════════════════════════╮\n"); 
printf("║\tsno\t\tsname\t\tscore\t║\n"); 
LinkList * p = L -> next; 
while(p) 
{ 
	printf("║\t%s\t\t%s\t\t%-4d\t║\n", p->data.sno, p->data.sname, p->data.score); 
	p = p -> next; 
} 
 printf("╰═══════════════════════════════════════════════╯\n\n"); 
} 
LinkList * createTailList() 
{ 
 //链表头结点 
 LinkList * L = (LinkList *)malloc(sizeof(LinkList)); 
 //结点 
 LinkList * s = NULL; 
 //尾结点 
 LinkList * r = L; 
           
 printf("╭═══════════════════════════════════════════════╮\n"); 
 printf("║\t\t尾插法建立\t\t\t║\n"); 
 printf("║\t请输入学生信息（当学号为\"#\"时结束）\t║\n"); 
 printf("║\t\t\t\t\t\t║\n"); 
 printf("║\t学号sno  （不超过4位）\t\t║\n"); 
 printf("║\t姓名sname （不超过4个汉字）\t\t║\n"); 
 printf("║\t成绩score （int型）\t\t\t║\n"); 
 printf("╰═══════════════════════════════════════════════╯\n\n"); 
           
 while (1) { 
  s = inputdata(); 
  if (!s) { 
   break; 
  } 
  r->next = s; 
  r = s; 
 } 
 r->next = NULL; 
 return L; 
} 
  
LinkList * createHeadList() 
{ 
 //链表头结点 
 LinkList * L = (LinkList *)malloc(sizeof(LinkList)); 
 //结点 
 LinkList * s = NULL; 
   
 printf("╭═══════════════════════════════════════════════╮\n"); 
 printf("║\t\t头插法建立\t\t║\n"); 
 printf("║\t请输入学生信息（当学号为\"#\"时结束）\t║\n"); 
 printf("║\t\t\t\t\t\t║\n"); 
 printf("║\t学号sno  （不超过4位）\t\t║\n"); 
 printf("║\t姓名sname （不超过4个汉字）\t\t║\n"); 
 printf("║\t成绩score （int型）\t\t\t║\n"); 
 printf("╰═══════════════════════════════════════════════╯\n\n"); 
 while (1) { 
  s = inputdata(); 
  if (!s) { 
   break; 
  } 
  s->next = L->next; 
  L->next = s; 
 } 
 return L; 
} 
  
void getElem(LinkList * L, int i) 
{ 
 LinkList * p = L; 
 int j = 0; 
 while (p && j<i) { 
  p = p->next; 
  j++; 
 } 
 if (!p) { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 else
 { 
  display(p); 
 } 
} 
  
void locateElemBysno(LinkList * L, char ch[5]) 
{ 
 LinkList * p = L->next; 
 while (p && (0 != strcmp(p->data.sno, ch))) 
 { 
  p = p -> next; 
 } 
 if (!p) { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 else
 { 
  display(p); 
 } 
} 
void locateElemBysname(LinkList * L, char ch[9]) 
{ 
 LinkList * p = L->next; 
 while (p && (0 != strcmp(p->data.sname, ch))) 
 { 
  p = p -> next; 
 } 
 if (!p) { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 else
 { 
  display(p); 
 } 
} 
int lengthList(LinkList * L) 
{ 
 LinkList * p = L->next; 
 int j = 0; 
 while (p) { 
  p = p->next; 
  j ++; 
 } 
 return j; 
} 
void insertElem(LinkList * L, int i) 
{ 
 LinkList * s = inputdata(); 
 LinkList * p = L; 
 int j = 0; 
 while (p && j<i-1) 
 { 
  p = p->next; 
  j++; 
 } 
 if (p && p->next) 
 { 
  s->next = p->next; 
  p->next = s; 
 } 
 else
 { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 displayAll(L); 
  
} 
  
void insertElemBysno(LinkList * L, char ch[5]) 
{ 
 LinkList * p = L; 
 LinkList * s = NULL; 
   
 while (p && (0 != strcmp(p->data.sno, ch))) 
 { 
  p = p->next; 
 } 
 if (!p) { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 else
 { 
  s = inputdata(); 
  s->next = p->next; 
  p->next = s; 
 } 
} 
  
void deleteElem(LinkList * L, char ch[5]) 
{ 
 LinkList *p, *q; 
 p = L->next; 
 q=L; 
 while (p && (strcmp(p->data.sno, ch) != 0)) { 
  q = p; 
  p = p->next; 
 } 
 if (!p) { 
  printf("╭═══════════════════════════════╮\n"); 
  printf("║\tDon't find the student!\t║\n"); 
  printf("╰═══════════════════════════════╯\n\n"); 
 } 
 else
 { 
  display(p); 
  q->next = p->next; 
  free(p); 
 } 
} 
void insertSort(LinkList * L) 
{ 
 LinkList * L1; 
 LinkList * p; 
 LinkList * q; 
 LinkList * s; 
 int len; 
 len = lengthList(L); 
 L1 = (LinkList *)malloc(sizeof(LinkList)); 
 if (L->next) { 
  s = (LinkList *)malloc(sizeof(LinkList)); 
  strcpy(s->data.sno, L->data.sno); 
  strcpy(s->data.sname, L->data.sname); 
  s->data.score = L->data.score; 
  s->next = NULL; 
  L1->next = s; 
  q = L->next; 
 } 
 else
 { 
  printf("╭═══════════════════════════════════╮\n"); 
  printf("║\tThe student link list is empty!\n║\n"); 
  printf("╰═══════════════════════════════════╯\n\n"); 
  
  return; 
 } 
 while (q) { 
  p = L1->next; 
  while (p &&(p->data.score >= q->data.score)) 
  { 
   p = p->next; 
  } 
  s = (LinkList *)malloc(sizeof(LinkList)); 
  strcpy(s->data.sno, q->data.sno); 
  strcpy(s->data.sname, q->data.sname); 
  s->data.score = q->data.score; 
  if (!p) { 
   s->next = NULL; 
   p->next = s; 
  } 
  else
  { 
   s->next = p->next; 
   p->next = s; 
  } 
  q = q->next; 
 } 
 displayAll(L1); 
}
