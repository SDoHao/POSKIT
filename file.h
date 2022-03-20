#ifndef FILE_H
#define FILE_H

#include<stdio.h>
void load_PTE_file();
void print_PTE();
POSCAR load_file(int param, char path[100]);
void print_file(POSCAR poscar);
int fix_file(struct POSCAR * poscar);
int fix_by_height(struct POSCAR * poscar, double min, double max);
int fix_by_elem(POSCAR * poscar, int n, char elem[][100]);
int fix_by_lines(POSCAR * poscar, int st,int ed);
void FixInfoOutput(int n);
void save_file(POSCAR poscar, int f, char path[100]);
void unfix_file(POSCAR * poscar);
void print_PWD();

#endif