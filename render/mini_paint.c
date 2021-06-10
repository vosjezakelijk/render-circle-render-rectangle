
# include "mini_paint.h"

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
	float dist;

	dist = sqrtf(powf(x - z->x, 2.0) + powf(y - z->y, 2.0));
	if (dist <= z->r)
	{
		if (z->r - dist < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
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
			if ((z->t == 'c' && pos == 2) || (z->t == 'C' && pos))
				(arr)[(y * z->w) + x] = z->f;
			y++;
		}
		x++;
	}
}	

int	check_c(t_z *z, FILE *file, char *arr)
{
	int par;

	while ((par = fscanf(file, "%c %f %f %f %c\n", &z->t, &z->x, &z->y, &z->r, &z->f)) != -1)
	{
		if ((par == 5 && z->r > 0.00000000 && (z->t == 'c' || z->t == 'C')))
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

void	draw_c(t_z *z, char *arr)
{
	int y;
	
	y = 0;
	while(y < z->h)
	{
		write(1, arr + (y * z->w), z->w);
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
	if (check_c(&z, file, arr) != 0)
	{
		print_error("Error: Operation file corrupted\n");
		return (1);
	}	
	draw_c(&z, arr);
	fclose(file);
	if (arr)		
		free(arr);
	return (0);
}
