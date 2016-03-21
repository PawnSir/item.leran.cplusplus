#include <stdio.h>
#include "anntacon.h"
int main()
{
	Con_State ret = Con_FAIL;
	ret=annotaCon();
	if (ret == Con_SUCCESS)
	{
		printf("×¢ÊÍ×ª»»³É¹¦£¡\n");
	}
	else
	{
		printf("×¢ÊÍ×ª»»Ê§°Ü£¡\n");
	}
	system("pause");
	return 0;
}