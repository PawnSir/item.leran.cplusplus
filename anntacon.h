#include <stdio.h>
#include <errno.h>
#include <assert.h>
typedef enum Con_State
{
	Con_SUCCESS,
	Con_FAIL
}Con_State;
typedef enum State
{
	C_BEGIN,
	C_END
}State;
Con_State Convert(FILE*fout, FILE*fin)
{
	int flag = C_END;//匹配问题
	char first=0;
	char second=0;
	char next = 0;
	assert(fout);
	assert(fin);
	while ((first = fgetc(fout)) != EOF)
	{
		switch (first)
		{
		case '/':
			second = fgetc(fout);
			if ((second == '*')&&flag==C_END)
			{
				flag = C_BEGIN;
				fputc('/', fin);
				fputc('/', fin);
			}
			else if (second == '/')//C++注释问题
			{
				fputc(first, fin);
				fputc(second, fin);
				fputc('\n', fin);
			}
			else
			{
				fputc(first, fin);
				fputc(second, fin);
			}
			break;
		case '\n'://多行注释问题
			if (flag == C_BEGIN)
			{
				fputc(first, fin);
				fputc('/', fin);
				fputc('/', fin);
			}
			else
			{
				fputc(first, fin);
			}
			break;
		case '*':
			second = fgetc(fout);
			if ((second == '/')&&(flag==C_BEGIN))
			{
				flag = C_END;
				if (((next = fgetc(fout)) != '\n')&&(next!=EOF))//换行问题,连续注释问题
				{
					fputc('\n', fin);
				}
				fseek(fout, -1, SEEK_CUR);//连续的** / 问题
			}
			else
			{
				fputc(first, fin);
				fseek(fout, -1, SEEK_CUR);//连续的** / 问题
			}
			break;
		default:
			fputc(first, fin);
			break;
		}
	}
	return Con_SUCCESS;
}
Con_State annotaCon()
{
	FILE* fout;
	FILE* fin;
	int ret = 0;
	fout = fopen("output.c", "r");
	if (fout == NULL)
	{
		printf("打开%s失败error:%d\n", "output", errno);
		return Con_FAIL;
	}
	fin = fopen("input.c", "w");
	if (fin == NULL)
	{
		printf("打开%s失败error:%d\n", "input", errno);
		fclose(fout);
		return Con_FAIL;
	}
	ret=Convert(fout, fin);
	fclose(fout);
	fclose(fin);
	return ret;
}