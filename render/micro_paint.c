/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro_paint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsamatha <hsamatha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 12:46:22 by hsamatha          #+#    #+#             */
/*   Updated: 2021/06/10 16:18:23 by hsamatha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_z
{
	int w;
	int h;
	char b;
	char t;
	float x;
	float y;
	float W;
    float H;
	char f;
}		t_z;

int	ft_strlen(char *txt)
{
	int i;

	i = 0;
	while(txt[i])
		i++;
	return (i);
}

void	print_error(char *txt)
{
	write(1, txt, ft_strlen(txt));
}

int	check_z(t_z *z, FILE *file)
{
    int param;
    
	param = fscanf(file, "%d %d %c\n", &z->w, &z->h, &z->b);
    if (param != 3)
    {
        fclose(file);
		return (1);
    }
	if (z->w < 1 || z->h < 1 || z->w > 300 || z->h > 300)
	{
		fclose(file);
		return (1);
	}
	return (0);
}


char	*draw_z(t_z *z)
{
	char *arr;
	int i;

	arr = (char *)malloc(z->w * z->h);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (z->w * z->h))
		arr[i++] = z->b;
	return (arr);
}

int	in_c(float x, float y, t_z *z)
{
    if	(x < z->x || ( z->x + z->W ) < x
    || y < z->y ||  ( z->y + z->H ) < y) 
        return (0);//miss
    if ((x - z->x) < 1.00000000 || (z->x + z->W - x)< 1.00000000 
    || (y - z->y) < 1.00000000 || (z->y + z->H - y) < 1.00000000)
        return (2);// border r
    return (1); // inside R 
}

void	def_r(t_z *z, char *arr)
{
	int x;
	int y;
	int pos;

	x = 0;
	while (x < z->w)
	{
		y = 0;
		while (y < z->h)
		{	
			pos = in_c((float)x, (float)y, z);
			if ((z->t == 'r' && pos == 2) || (z->t == 'R' && pos))
				(arr)[(y * z->w) + x] = z->f;
			y++;
		}
		x++;
	}
}	

int	chack_r(t_z *z, FILE *file, char *arr)
{
	int par;

	while ((par = fscanf(file, "%c %f %f %f %f %c\n", &z->t, &z->x, &z->y, &z->W, &z->H, &z->f)) != -1)
	{
		if ((par == 6 && z->W > 0.00000000 && z->H > 0.00000000 && (z->t == 'r' || z->t == 'R')))
        	def_r(z, arr);
        else
		{
			fclose(file);
			if (arr)		
				free(arr);
			return (1);
		}
	}
	return (0);
}		

void	draw_r(t_z *z, char *arr)
{
	int y;
	
	y = 0;
	while(y < z->h)
	{
		write(1, arr + (1 * z->w), z->w);
		write(1, "\n", 1);
		y++;
	}
}


int	main(int argc, char **argv)
{
	FILE *file;
	char *arr;
	t_z z;

	if (argc != 2)
	{
		print_error("Error: argument\n");
		return (1);
	}
	if (!(file = fopen(argv[1], "r")))
	{
		print_error("Error: Operation file corrupted\n");
		return (1);
	}
	if (check_z(&z, file) != 0)
	{
		print_error("Error: Operation file corrupted\n");
		return (1);
	}
	arr = draw_z(&z);
	if (chack_r(&z, file, arr) != 0)
	{
		print_error("Error: Operation file corrupted\n");
		return (1);
	}	
	draw_r(&z, arr);
	fclose(file);
	if (arr)		
		free(arr);
	return (0);
}
