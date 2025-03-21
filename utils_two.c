/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:39:23 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 07:39:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	close_window(t_data *data)
{
	mlx_destroy_image(data->mlx, data->img.img);
	mlx_destroy_window(data->mlx, data->win);
	free_map(data->map);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	exit(0);
	return (0);
}

void	*cleaner(t_map *map)
{
	int	y;

	y = 0;
	if (map->points)
	{
		while (y < map->height)
		{
			free(map->points[y]);
			y++;
		}
		free(map->points);
	}
	if (map)
		free(map);
	return (NULL);
}

int	handle_key(int keycode, t_data *data)
{
	if (keycode == 53 || keycode == 65307)
	{
		close_window(data);
	}
	return (0);
}

int	allocate_points(t_map *map)
{
	int	y;

	y = 0;
	map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
	if (!map->points)
	{
		return (0);
	}
	while (y < map->height)
	{
		map->points[y] = (t_point *)malloc(sizeof(t_point) * map->width);
		if (!map->points[y])
			return (0);
		y++;
	}
	return (1);
}
