#pragma once
#include<stdio.h>
void load_PTE_file();
struct POSCAR load_file();
void print_file(POSCAR poscar);
int fix_file(struct POSCAR * poscar);
int fix_by_height(struct POSCAR * poscar, double min, double max);
int fix_by_elem(POSCAR * poscar, int n, char elem[][3]);
int fix_by_lines(POSCAR * poscar, int st,int ed);
void FixInfoOutput(int n);
void save_file(POSCAR poscar);