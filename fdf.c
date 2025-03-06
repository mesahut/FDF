#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include "fdf.h"

void	ft_read_map(char *file_name)
{
	t_map	*map;
	int		fd;
	int		i;

	i = 0;
	map->col_len = 0;
	fd = open(file_name, O_RDONLY);
	while (get_next_line(fd))
		map->col_len++;
	map->map = (char **)malloc(sizeof(char *) * (map->col_len + 1));
	map->map[map->col_len] = NULL;
	while (get_next_line(fd))
	{
		map->map[i] = get_next_line(fd);
		i++;
	}
}

void	ft_parse_map(t_map *map)
{
	int		i;
	
	i = 0;
	while (map->map)
	{
		map->row = ft_split(map->map[i], ' ');
		draw_point(map->row);
		i++;
	}
}

void	draw_point(char **row)
{

}

int main(int argc, char **argv)
{
	if(argc != 2)
		return(0);
		t_mlx	*mlx;
		
	ft_check_map(argv[1]);
	mlx->begin = mlx_init();
	mlx->win = mlx_new_mlx(mlx->begin, WIDTH, HEIGHT, "FDF");
	mlx->img = mlx_new_image(mlx->begin, WIDTH, HEIGHT);
	mlx->data = mlx_get_data_addr(mlx->begin, &mlx->bit, &mlx->len, mlx->check);
	ft_read_map(argv[1]);
}
