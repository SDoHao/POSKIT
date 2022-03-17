#include<stdio.h>
#include <string.h>
#include <ctype.h>
//ȥ��β���ո�
char *RTrim(char *str)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
	int len = strlen(str);
	char *p = str + len - 1;
	while (p >= str  && isspace(*p))
	{
		*p = '\0';
		--p;
	}
	return str;
}

//ȥ���ײ��ո�
char *LTrim(char *str)
{
	if (str == NULL || *str == '\0')
	{
		return str;
	}
	int len = 0;
	char *p = str;
	while (*p != '\0' && isspace(*p))
	{
		++p;
		++len;
	}
	memmove(str, p, strlen(str) - len + 1);
	return str;
}

//ȥ����β�ո�
char *Trim(char *str)
{
	str = RTrim(str);
	str = LTrim(str);
	return str;
}