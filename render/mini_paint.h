#ifndef MINI_PAINT_H
# define MINI_PAINT_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct s_z
{
	int w;
	int h;
	char b;
	char t;
	float x;
	float y;
	float r;
	char f;
}		        t_z;

int main(int argc, char **argv);

# endif