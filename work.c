#include <stdio.h>
#include "anntacon.h"
int main()
{
	Con_State ret = Con_FAIL;
	ret=annotaCon();
	if (ret == Con_SUCCESS)
	{
		printf("ע��ת���ɹ���\n");
	}
	else
	{
		printf("ע��ת��ʧ�ܣ�\n");
	}
	system("pause");
	return 0;
}