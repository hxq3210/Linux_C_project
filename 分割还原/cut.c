/*************************************************************************
  > 文件名称 : demo3.c
  > 创 建 者 : hxq
  > E--mail  : 1038403210@qq.com
  > 创建时间 : 2018年07月31日21时57分54秒
  > 描   述  : 
 *************************************************************************/
#define  _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 6   // 定义分割块数
void main()
{
	FILE *fsrc = fopen("./a.out", "rb");  // 源文件
	FILE *div = fopen("./div.txt","w");  // 存入分割条目的信息
	if (fsrc == NULL || div == NULL)
	{
		perror("打开错误：");
		return;
	}
	fseek(fsrc, 0, SEEK_END); 
	int fLen = ftell(fsrc);  // 文件长度
	//printf("文件长度：%d\n", fLen);
	int blockLen = fLen / N;   // 每一块的长度
	//printf("blockLen:%d\n", blockLen);
	FILE *ftmp;  // 临时文件，
	for (int i = 0; i < N; i++)  // 按块分割
	{
		char tName[20];
		char tdir[60] = "./";
		sprintf(tName, "部分%d.tmp", i+1);//生成文件名
		strcat(tdir, tName);  //产生临时目录
		//printf("%s\n", tdir);
		ftmp = fopen(tdir, "wb");  // 生成临时文件
		if (ftmp == NULL)
		{
			perror("产生文件出错：");
			break;
		}
		fputs(tdir, div); // 写入文件名
		fputc('\n',div);

		int offset = i*blockLen; //计算偏移量
		fseek(fsrc, offset, SEEK_SET);
		int count = 0;  //统计写入ftmp的数量
		if (i == N - 1) blockLen = fLen - blockLen*(N - 1);  //最后一块的长度
		while (count<blockLen && !feof(fsrc))
		{

			fputc(fgetc(fsrc),ftmp);
			count++;
		}
		printf("count:%d\n", count);
		fclose(ftmp);
	}

	fclose(fsrc);
	fclose(div);

	system("pause");
}

