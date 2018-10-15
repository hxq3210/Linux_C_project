/*************************************************************************
    > 文件名称 : 1.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日09时25分06秒
    > 描   述  : 用递归算法判断数组a[N]是否为一个递增数组
 ************************************************************************/
#include<stdio.h>
int pd_array(int a[],int n)
{
	if(n==1)
		return 0;
	else
	{
		if(a[n-1]>a[n-2])
		{
			return pd_array(a,n-1);
		}
		else return 1;
	}
}
int main(int argc, char *argv[])
{
	int a[]={0};
	int N=0,ret=0,i=0;
	printf("请输入数组元素个数\n");
	scanf("%d",&N);
	for(i=0;i<N;i++)
	{
		printf("请输入第%d个元素的值\n",i);
		scanf("%d",&a[i]);
	}
	ret = pd_array(a,N);
	if(ret==0)
	{
		printf("该数组是递增数组\n");
	}
	if(ret==1)
	{
		printf("该数组不是递增数组\n");
	}
    return 0;
}
