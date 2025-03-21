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

#include "fdf.h"

void	calculate_scale(t_data *data, float scale_x, float scale_y)
{
	float	height_diff;
	float	map_width_iso;
	float	map_height_iso;
	float	height_factor;

	height_diff = get_max_height(data->map) - get_min_height(data->map);
	map_width_iso = (data->map->width + data->map->height) * cos(0.5);
	height_factor = fmin(height_diff, height_diff * (WIDTH / (float)HEIGHT));
	map_height_iso = (data->map->width + data->map->height) * sin(0.5);
	map_height_iso += height_factor;
	scale_x = (WIDTH * 0.7) / map_width_iso;
	scale_y = (HEIGHT * 0.7) / map_height_iso;
	if (scale_x < scale_y)
		data->scale = scale_x;
	else
		data->scale = scale_y;
}

void	calculate_shift(t_data *data)
{
	float	center_x;
	float	center_y;
	float	iso_x;
	float	iso_y;

	center_x = (data->map->width - 1) / 2.0;
	center_y = (data->map->height - 1) / 2.0;
	iso_x = (center_x - center_y) * cos(0.5);
	iso_y = (center_x + center_y) * sin(0.5);
	data->shift_x = (WIDTH / 2) - (iso_x * data->scale);
	data->shift_y = (HEIGHT / 2) - (iso_y * data->scale);
}

void	init_data(t_data *data)
{
	float	scale_x;
	float	scale_y;

	scale_x = 0;
	scale_y = 0;
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF");
	data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_length, &data->img.endian);
	calculate_scale(data, scale_x, scale_y);
	calculate_shift(data);
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
