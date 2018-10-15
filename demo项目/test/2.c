/*************************************************************************
    > 文件名称 : 2.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日13时54分44秒
    > 描   述  : 用指针的方法，将字符串“ABCD1234efgh”前后对调显示 
 ************************************************************************/
#include<stdio.h>
#include<string.h>
int main(int argc, char *argv[])
{
	char s[]="ABCD1234efgh";
	char *p1=s;
	char *p2=s-1;
	while(*++p2);
	p2-=1;
	while(p1<p2)
	{
		char c;
		 c	= *p1;
		*p1 = *p2;
		*p2 =  c;
		p1++;
		p2--;
	}
	printf("%s\n",s);
    return 0;
}
