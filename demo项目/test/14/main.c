/*************************************************************************
    > 文件名称 : main.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日16时15分37秒
    > 描   述  : 
 ************************************************************************/
#include<stdio.h>
#include"seqstack.h"
int main(int argc, char *argv[])
{
	int d,i=0,a;
	int ret=0;
	seqstack *s = seqstack_create();
	seqstack *s1 = seqstack_create();
	if(NULL==s)
	{
		printf("顺序栈创建失败\n");
		return -1;
	}
	for(i=0;i<10;i++)
	{
		printf("请输入十个入栈元素\n");
		scanf("%d",&a);
		seqstack_push(s,a);
		printf("seqstack push = %d\n",a);
	}
	while(!seqstack_isempty(s))
	{
	    ret = seqstack_pop(s);
		seqstack_push(s1,ret);
	}

	while(!seqstack_isempty(s1))
	{
		seqstack_pop(s1);
		ret = seqstack_get_top_value(s1);
		printf("seqstack pop = %d\n",ret);
	}
	return 0;
}
