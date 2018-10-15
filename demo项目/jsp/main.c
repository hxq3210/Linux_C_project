/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年01月29日
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include<string.h>
#include"add.h"
#include"sub.h"
#include"mul.h"
#include"chu.h"
int main(int argc, char *argv[])
{
	int a = 0,b = 0,c = 0;
	char k;
	while(1)
	{
		printf("请输入两个数：\n");
		scanf("%d %d",&a,&b);
		printf("请输入加减乘除：\n");
		getchar();
		scanf("%c",&k);
		switch(k)
		{
			case '+':c = add(a,b);break;
			case '-':c = sub(a,b);break;
			case '*':c = mul(a,b);break;
			case '/':c = chu(a,b);break;
		}
		printf("%d %c %d = %d\n",a,k,b,c);
	    return 0;
	}
}
