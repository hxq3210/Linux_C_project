/*************************************************************************
    > 文件名称 : 5.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日14时36分00秒
    > 描   述  : 用递归方法写出斐波那契数列的通项式(f(n))，已知f1=1,f2=1;
				 以后每项都是前两项的和
 ************************************************************************/
#include<stdio.h>
int fun(int n)
{
	if((n==1)||(n==2)) return 1;
	else
	{
		return fun(n-1)+fun(n-2);
	}
}
int main(int argc, char *argv[])
{
	int a,ret;
	printf("请输入一个数\n");
	scanf("%d",&a);
	printf("斐波那契数是 %d\n",fun(a));
    return 0;
}
