/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:32:11 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 07:32:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"
#include "fdf.h"
#include <math.h>
#include <stdio.h>

void	init_data(t_data *data)
{
	float	scale_h;
	float	scale_w;

	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bit_pixel,
			&data->img.line_length, &data->img.endian);
	data->shift_x = WIDTH / 2;
	data->shift_y = HEIGHT / 2;
	scale_w = (WIDTH * 0.3) / data->map->width;
	scale_h = (HEIGHT * 0.3) / data->map->height;
	if (scale_w < scale_h)
		data->scale = scale_w;
	else
		data->scale = scale_h;
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_putstr("Error: Too many arguments.");
		return (1);
	}
	data.map = read_map(argv[1]);
	if (!data.map)
	{
		ft_putstr("Error: could not read the map.");
		return (1);
	}
	init_data(&data);
	draw(&data);
	mlx_key_hook(data.win, handle_key, &data);
	mlx_hook(data.win, 17, 1L << 17, close_window, &data);
	mlx_loop(data.mlx);
	return (0);
}
