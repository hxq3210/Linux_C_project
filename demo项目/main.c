/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月08日12时58分56秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define N 15
struct person
{
char name[10];
char phone[11];
char classify[10];
char email[20];
}per[N];
char A[]={"office"};
char B[]={"personal"};
char C[]={"business"};
int load()//**********加载函数**********/
/***********加载所有记录,并且可以返回所有记录的个数********/
{
FILE *fp;
int i;
if((fp=fopen("person.txt","r"))==NULL)
{
printf("\nCannot open file\n");
return 0;
}
for(i=0;!feof(fp);i++)
fscanf(fp,"%s%s%s%s",&per[i].name,&per[i].phone,&per[i].classify,&per[i].email);
fclose(fp);
return(i);
}
/***************查看功能**************/
search()
{
void menu();
int n,j,k=-1;
char p[10];
n=load();
printf("\n\nClassify A:office\nClassify B:single\nClassify C:business\n\n Enter classify that you want to search! Classify:"); /*************输入要找的人的分类*********/
scanf("%s",p);
for(j=0;j<n;j++)
if(strcmp(p,per[j].classify)==0)
{
k=j;
printf("\n(%d).%s %s\n",j,per[j].name,per[j].phone);
}
if(k==-1)
/**********如果要查找的分类不存在,则显示不存在**********/ {
printf("\n\nNO EXIST!");
}
menu();
}
/**************增加功能*********/
void add()
{
void menu(); int n,j;
FILE *fp;
char name[10],classify[10],email[20];
char phone[11];
n=load();
printf("\n\nThe name and phone of the person you want to add are:\n\n");
/******输入要增加人的姓名和电话号码******/
scanf("%s%s",name,phone);
if(!(fp=fopen("person.txt","r+"))==NULL)
{
printf("\n\nCan not open!\n\n");
}
for(j=0;j<n;j++)
{ if(strcmp(name,per[j].name)==0&&strcmp(phone,per[j].phone)==0)/*如果输入的姓名和电话已存在,则提示已存在*/
{
printf("\n\nThe message is exist!\n");break;
}
}
if(j==15)
{
//if(j>=15)
printf("\n\nThe room is full!\n\n");/*如果记录多余15条,则提示空间已满*/
}
else
{
printf("\nOK!Put the classify and email:\n");
/****如果输入的是新信息,则继续输入这个人的分类和电子邮件*****/ scanf("%s%s",classify,email);
fseek(fp,0,2);
fprintf(fp,"\n%s %s %s %s",name,phone,classify,email); }
fclose(fp);
menu();
}
/****************修改功能************/
void modify()
{
void menu() ;
int i,n,j,c; char name[10];
FILE *fp;
n=load();
printf("\n\nModify by name:\n");
/*****输入要修改人的姓名******/
scanf("%s",name);
if((fp=fopen("person.txt","r+"))==NULL)
{
printf("\n\nCan not open!\n\n");
}
for(j=0;j<n;j++)
if(strcmp(name,per[j].name)==0)
{
do
{ puts("\nModifyby=>\n\n1).name2).phone:3).classify:4).email:"); printf("Whitch you needed?:[ ]\b\b");
/*******输入要修改的选项********/
scanf("%d",&c);
if(c>4||c<1)
{
puts("\nChioce error!Please again!");
getchar();
}
}
while(c>8||c<1);break;
}
do
{ switch(c)
{
case 1:printf("name");scanf("%s",per[j].name);break;
case 2:printf("phone");scanf("%s",per[j].phone);break;
case 3:printf("classify");scanf("%s",per[j].classify);break;
case 4:printf("email");scanf("%s",per[j].email);break;
}
}
while(c<1||c>4);

if(j==n) printf("\n\nThe name you want is not exist!\n"); for(i=0;i<n;i++)
fprintf(fp,"%s %s %s %s\n",per[i].name,per[i].phone,per[i].classify,per[i].email);
fclose(fp);
menu ();
}
/******************删除功能****************/
void del() {
void menu();
int i,j,n;
FILE *fp;
char name[10];
n=load();
printf("\n\nDel by name:");
/******输入要删除人的姓名********/
scanf("%s",name);
if((fp=fopen("person.txt","w"))==NULL)
{
printf("\n\nCan not open!\n\n");
}
for(j=0;j<n;j++)
if(strcmp(name,per[j].name)==0)
break;
for(i=0;i<n;i++) if(i!=j)
/********删除选项,并自动调整其他所有选项*************/
fprintf(fp,"%s%s%s%s\n",per[i].name,per[i].phone,per[i].classify,per[i].email);
fclose(fp);
menu();
}
/****************显示功能***************/
void browse() {
void menu();
int n,i;
n=load();
for(i=0;i<n;i++) {
printf("\n(%d).%s-%s-%s-%s\n",i,per[i].name,per[i].phone,per[i].classify,per[i].email);
}
menu();
}
/***************菜单*****************/
void menu()
{
int n,w1;/*变量n保存选择菜单数字,w判断输入的数字是否在功能菜单对应数字范围内*/
do
{
puts("\t\t**********通讯录主界面**********\n\n");
puts("\t\t\t\t 1. 查询成员资料"); puts("\t\t\t\t 2. 增加一位成员资料");
puts("\t\t\t\t 3. 修改一位成员资料"); puts("\t\t\t\t 4. 删除一位成员资料");
puts("\t\t\t\t 5. 成员总名单查看");
puts("\t\t\t\t 6. 退出系统"); puts("\n\n\t\t*********************************\n"); printf("Choice your number(1-6):[ ]\b\b"); scanf("%d",&n); if(n<1||n>6)
{w1=1;getchar();}
else w1=0;
}
while(w1==1);
switch(n)
{
case 1:search();break; /*查看模块*/
case 2:add();break; /*增加模块*/
case 3:modify();break; /*修改模块*/
case 4:del();break; /*删除模块*/
case 5:browse();break; /*显示模块*/
case 6:exit(0); /*退出*/
}
}
/***************主函数****************/
main ()
{
menu ();
}
