/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日20时02分27秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"address.h"
int main(int argc, char *argv[])
{
	link l;
	l = (Node*)malloc(sizeof(Node));
	if(!l)
	{
		printf("未申请到，请按提示信息输入~\n");
		return;
	}
	l->next = NULL;
	system("clear");
	while(1)
	{
		system("clear");
		switch(menu_select())
		{
			case 1: 
				enter(l);
				break;
			case 2:
				del(l);
				break;
			case 3:
				list(l);
				break;
			case 4:
				search(l);
				break;
			case 5:
				exit(0);

		}
	}
    return 0;
}
