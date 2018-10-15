/*************************************************************************
    > 文件名称 : 7.c
    > 创 建 者 : hxq
    > E--mail  : 1038403210@qq.com
    > 创建时间 : 2018年02月07日15时07分38秒
    > 描   述  : 将输入的字符串倒序输出
 ************************************************************************/
#include<stdio.h>
#include<string.h>
void revert(char *str)
{
	int len = strlen(str);
	char c;
	int i=0;
	while(i!=len/2)
	{
		c = str[i];
		str[i] = str[len-i-1];
		str[len-i-1]=c;
		i++;
	}
}
int main(int argc, char *argv[])
{
	char str[128];
	printf("请输入源字符串\n");
	gets(str);
	printf("源字符串：%s\n",str);
	revert(str);
	printf("倒序：%s\n",str);
    return 0;
}
