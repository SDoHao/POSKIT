#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include <string.h>
#include"poscar.h"
const char SD[18] = "Selected dymanics";
const char TableofElements[118][3];

void load_PTE_file()
{
	FILE *table = NULL;
	int i;
	table = fopen("./PeriodicTableofElements", "r");
	if(table == NULL)
		printf("\n    MISSING Periodic Table of Elements\n\n");
	else
	{
		for (i = 0; i < 118; i++)
			fscanf(table, "%s", TableofElements[i]);
		fclose(table);
	}
		
}
void print_PTE()
{
	int i;
	printf("\nThis is a Periodic Table of Elements:\n  ");
	for (i = 0; i < 118; )
	{
		printf("%3d %3s  ", i + 1, TableofElements[i]);
		if ((++i) % 5 == 0)
			printf("\n  ");
	}
	printf("\n\n");
}

POSCAR load_file()
{
	POSCAR poscar;
	int i, j, elem_num = 0;
	char strings[100],command1[12], command2[12];
	char *trim_string,is_F_or_T[2];
	
	FILE *pos = NULL;
	pos = fopen("./POSCAR", "r");
	if (pos == NULL)
		pos = fopen("./CONTCAR", "r");
	if (pos == NULL)
	{
		poscar.suc = 0;
		printf("\n    File read failed\n");
	}
	else
	{
		poscar.suc = 1;
		fscanf(pos, "%s", &poscar.name);
		fscanf(pos, "%f", &poscar.scale);
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				fscanf(pos, "%lf", &poscar.lattice[i][j]);
		//读取换行符
		fgets(strings, 5, pos);
		//读取元素
		fgets(strings, 100, pos);
		trim_string = &strings[0];
		//trim_string = Trim(strings);
		while (*trim_string != '\0')
		{
			char c = *trim_string;
			if ('a' <= c && c <= 'z')
			{
				poscar.element[elem_num - 1][1] = c;
				poscar.element[elem_num - 1][2] = '\0';
			}
			else if ('A' <= c && c <= 'Z')
			{
				poscar.element[elem_num][0] = c;
				poscar.element[elem_num++][1] = '\0';
			}
			trim_string++;
		}
		poscar.elem_num = elem_num;
		//读取元素数量
		poscar.total_num = i = 0;
		while (i < elem_num)
		{
			fscanf(pos, "%d", &poscar.atom_num[i]);
			poscar.total_num += poscar.atom_num[i++];
		}
		//是否固定以及坐标类型
		fscanf(pos, "%s", command1);
		if (command1[0] == 'S')
		{
			poscar.is_selective = 1;
			fscanf(pos, "%s", command2);
			fscanf(pos, "%s", poscar.pos_type);
		}
		else
		{
			poscar.is_selective = 0;
			strcpy(poscar.pos_type, command1);
		}
		//读取坐标
		for (i = 0; i < poscar.total_num; i++)
		{
			for (j = 0; j < 3; j++)
			{
				fscanf(pos, "%lf", &poscar.position[i][j]);
			}
			if (poscar.is_selective)
			{
				for (j = 0; j < 3; j++)
				{
					fscanf(pos, "%s", &is_F_or_T);
					if (is_F_or_T[0] == 'F')
					{

						poscar.isFixed[i][j] = 1;
					}
					else
						poscar.isFixed[i][j] = 0;
				}
			}
		}
		fclose(pos);
		printf("\n    File read succeeded.\n\n");
	}
	return poscar;
}

void print_file(POSCAR poscar)
{
	//输出
	if (poscar.suc == 0)
	{
		printf("\n    Nothing output.\n\n"); 
		return;
	}	
	int i,j,t,ct,index;
	printf("%s\n%.12f\n", poscar.name, poscar.scale);
	for (i = 0; i < 3; i++)
	{
		printf("    ");
		for (j = 0; j < 3; j++)
		{
			printf("%17.16lf ", poscar.lattice[i][j]);
			if (j == 2)
				printf("\n");
		}
	}
	//输出元素种类
	for (i = 0; i < poscar.elem_num; i++)
	{
		printf("%3s ", poscar.element[i]);
	}
	printf("\n");
	//输出元素数量
	for (i = 0; i < poscar.elem_num; i++)
		printf("%3d ", poscar.atom_num[i]);
	printf("\n#there are %d atoms\n", poscar.total_num);
	//printf("\n");
	//是否固定
	if (poscar.is_selective)
	{
		printf("%s\n", SD);
	}
	//坐标类型
	printf("%s\n", poscar.pos_type);
	index = ct = 0;
	t = poscar.atom_num[0];
	for (i = 0; i < poscar.total_num; i++)
	{
		printf("%3d ", i + 1);
		printf("%2s ", poscar.element[index]);
		if (++ct == t)
		{
			ct = 0;
			t = poscar.atom_num[++index];
		}
		for (j = 0; j < 3; j++)
		{
			printf("%17.16lf ", poscar.position[i][j]);
		}
		if (poscar.is_selective)
		{
			for (j = 0; j < 3; j++)
			{
				if (poscar.isFixed[i][j])
					printf("F ");
				else
					printf("T ");
			}
		}
		printf("\n");
	}
}

int fix_file(POSCAR * poscar)
{
	int flag = 0;
	if (poscar->is_selective)
		printf("It has alerady been fixed!\n");
	else
	{
		int i, j;
		poscar->is_selective = 1;
		for (i = 0; i < poscar->total_num; i++)
			flag++;
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 1;
			}
	}
	return flag;
}

int fix_by_height(POSCAR * poscar,double min, double max)
{
	int flag;
	int i, j;
	double z;
	flag = i = 0;
	for (; i < poscar->total_num; i++)
	{
		z = poscar->position[i][2];
		if (z >= min && z <= max)
		{
			flag++;
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 1;
			}
		}
		else
		{
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 0;
			}
		}
	}
	return flag;
}

int fix_by_elem(POSCAR * poscar,int n,char elem[][100])
{
	int i, j, t, flag = 0, is_re, index = 0, ct = 0, max;
	int total = poscar->total_num;
	if(n > 1)
	{
		printf("\n    You are about to fix the follnowing atoms.\n    ");
		//预处理元素
		for (i = 1; i < n; i++)
		{
			elem[i][2] = '\0';
			if (elem[i][1] >= 'A' && elem[i][1] <= 'Z')
				elem[i][1] += 32;
		}
		//去除重复元素
		if (n > 2)
		{
			for (i = 1; i < n; i++)
			{
				for (is_re = 0, j = i + 1; j < n; j++)
				{
					if (elem[j][0] == '\0')break;
					for (t = 0; t < 3; t++)
					{
						if (elem[i][t] != '\0')
						{
							if (elem[i][t] == elem[j][t])
								is_re = 1;
							else
								is_re = 0;
						}
						else
						{
							if (elem[j][t] == '\0')
								break;
							else
								is_re = 0;
						}
					}
					if (is_re)
						elem[j][0] = '\0';
				}
			}
		}
		for (i = 1; i < n; i++)
		{
			if(elem[i][0] != '\0')
				printf("%s ", elem[i]);
		}
		printf("\n");
		for (i = 0; i < total; i++)
			for (j = 0; j < 3; j++)
			{
					poscar->isFixed[i][j] = 0;
			}
		max = poscar->atom_num[index];
		for (i = 0; i < total; i++)
		{
			if (ct++ == max)
			{
				ct = 1;
				max = poscar->atom_num[++index];
			}
			for (j = 1; j < n; j++)
			{
				is_re = strcmp(poscar->element[index], elem[j]);
				//printf("%d %d %s %s %d\n",i + 1, index,poscar->element[index], elem[j], is_re);
				if (is_re == 0)
				{
					flag++;
					for (t = 0; t < 3; t++)
						poscar->isFixed[i][t] = 1;
					break;
				}
			}
		}
	}
	return flag;
}

int fix_by_lines(POSCAR * poscar, int st,int ed)
{
	int flag;
	int i, j,total;
	flag = i = 0;
	total = poscar->total_num;
	if (st >= 0)
	{
		if (ed > total)
			ed = total;
		else
			;
		if (st == ed)
		{
			if (st == 0)return 0;
			for (i = 0; i < total; i++)
				for (j = 0; j < 3; j++)
				{
					if(st == i + 1)
						poscar->isFixed[i][j] = 1;
					else
						poscar->isFixed[i][j] = 0;
				}
			return 1;
		}
		if (st == 0)
			st = 1;
		for (i = 0; i < st; i++)
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 0;
			}
		for (i = st - 1; i < ed; i++)
		{
			if (ed > total)break;
			flag++;
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 1;
			}
		}
		for (i = ed; i < total; i++)
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 0;
			}
	}
	else
	{ 
		if (total < -st)st = -total;
		for (i = 0; i < total + st; i++)
		{
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 0;
			}
		}
		for (i = total + st; i < total; i++)
		{
			flag++;
			for (j = 0; j < 3; j++)
			{
				poscar->isFixed[i][j] = 1;
			}
		}
	}
	return flag;
}

void unfix_file(POSCAR * poscar)
{
	int i, j;
	poscar->is_selective = 0;
	for (i = 0; i < poscar->total_num; i++)
	{
		for (j = 0; j < 3; j++)
		{
			poscar->isFixed[i][j] = 0;
		}
	}
	printf("\n    All atoms are unfixed.\n\n");
}

void FixInfoOutput(int n)
{
	//printf("-----------------------------\n");
	printf("                             \n");
	if (n > 0)
	{
		if (n == 1)
			printf("    A total of one atom is fixed");
		else
			printf("    A total of %d atoms are fixed\n", n);
	}
	else
	{
		printf("    No atoms are fixed\n");
	}
	printf("                             \n");
	//printf("-----------------------------\n");
}

void save_file(POSCAR poscar,int f)
{
	if (poscar.suc == 0)
	{
		printf("\n    Nothing output.\n\n");
		return;
	}
	//printf("-----------------------------\n");
	int i, j, t, ct, index;
	FILE *fp = NULL;
	if(f)
		fp = fopen("POSCAR_new", "w+");
	else
		fp = fopen("POSCAR", "w+");
	fprintf(fp, "%s\n%.12f\n", poscar.name, poscar.scale);
	for (i = 0; i < 3; i++)
	{
		fprintf(fp, "    ");
		for (j = 0; j < 3; j++)
		{
			fprintf(fp, "%17.16lf ", poscar.lattice[i][j]);
			if (j == 2)
				fputs("\n", fp);
		}
	}
	for (i = 0; i < poscar.elem_num; i++)
	{
		fprintf(fp, "%3s ",poscar.element[i]);
	}
	fprintf(fp, "\n");
	for (i = 0; i < poscar.elem_num; i++)
		fprintf(fp, "%3d ", poscar.atom_num[i]);
	fprintf(fp, "\n");
	if (poscar.is_selective)
	{
		fprintf(fp, "%s\n", SD);
	}
	fprintf(fp, "%s\n", poscar.pos_type);
	index = ct = 0;
	t = poscar.atom_num[0];
	for (i = 0; i < poscar.total_num; i++)
	{
		if (++ct == t)
		{
			ct = 0;
			t = poscar.atom_num[++index];
		}
		for (j = 0; j < 3; j++)
		{
			fprintf(fp, "%17.16lf ",poscar.position[i][j]);
		}
		if (poscar.is_selective)
		{
			for (j = 0; j < 3; j++)
			{
				if (poscar.isFixed[i][j])
					fputs("F ", fp);
				else
					fputs("T ", fp);
			}
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
	printf("\n    Output file succeeded.\n\n");
	//printf("-----------------------------\n");
}