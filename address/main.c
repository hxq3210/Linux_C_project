/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月12日14时53分31秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>

int main(int argc, char *argv[])
{ 
	struct address_list *head=NULL; 
	char num[10]; 
	system("clear");
	printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n"); 
    printf("*=*              程序说明                 *=*\n"); 
    printf("*=*   请及时保存创建完毕的通讯录内容!     *=*\n"); 
    printf("*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*=*\n"); 
    while(1) 
   {
		printf("\t************************\n"); 
		printf("\t***   1 创建通讯录   ***\n"); 
		printf("\t***   2 按名字排序   ***\n"); 
	    printf("\t***   3 综合操作     ***\n"); 
	    printf("\t***   4  保 存       ***\n"); 
	    printf("\t***   5  打 开       ***\n");  
	    printf("\t***   6  删 除       ***\n"); 
	    printf("\t***   7  退 出       ***\n"); 
	    printf("\t************************\n"); 
	    printf("请输入您选择的操作:"); 
	    gets(num); 
	    switch(*num) 
	    { 
	    case '1': 
			{ 
				if(head==NULL) 
				{ 
					head=creat();                //创建 
					print(head); 
				} 
		        else
				{ 
					head=shifang(head); 
		            head=creat();                //重新创建 
					print(head); 
				} 
			} 
			break; 
		case '2': 
			{ 
				head=paixu(head);                //排序 
			} 
			break; 
		case '3': 
			{	 
				head=menu(head);               //综合操作 
			}	 
			break; 
		case '4': 
			{ 
				save(head);                  //文件保存 
				print(head); 
			} 
			break; 
		case '5': 
			{	 
				head=load(head);               //文件输出 
			} 
			break; 
		case '6': 
			{ 
				head=delete_txl(head);              //删除 
				print(head); 
			}	 
			break; 
		case '7': 
			head=shifang(head); 
			break; 
		default: 
			printf("操作错误，此项不存在!\n"); 
			break; 
		} 
		if(strcmp(num,"7")==0) 
		break; 
	} 
} 
