/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:03:46 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 00:03:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

float	get_max_height(t_map *map)
{
	int		x;
	int		y;
	float	max_height;

	max_height = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z > max_height)
				max_height = map->points[y][x].z;
			x++;
		}
		y++;
	}
	return (max_height);
}

float	get_min_height(t_map *map)
{
	int		x;
	int		y;
	float	min_height;

	min_height = map->points[0][0].z;
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->points[y][x].z < min_height)
				min_height = map->points[y][x].z;
			x++;
		}
		y++;
	}
	return (min_height);
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

int	update_map(t_map *map, int fd)
{
	char	*line;
	int		y;

	y = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (count_words(line, ' ') > 0)
		{
			if (fill_points(map, line, y) == 0)
			{
				free(line);
				return (0);
			}
		}
		y++;
		free(line);
	}
	return (1);
}

int	get_map_data(t_map *map, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		return (0);
	}
	map->width = count_words(line, ' ');
	map->height = 1;
	free(line);
	while (line != NULL)
	{
		line = get_next_line(fd);
		if (count_words(line, ' ') > 0)
			map->height++;
		free(line);
	}
	return (1);
}
