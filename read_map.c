/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:47:49 by marvin            #+#    #+#             */
/*   Updated: 2025/03/20 23:47:49 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	count_words(char *line, char delimiter)
{
	int	count;
	int	in_word;

	in_word = 0;
	count = 0;
	while (*line)
	{
		if (*line != delimiter && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*line == delimiter)
			in_word = 0;
		line++;
	}
	return (count);
}

int	get_color(char *str)
{
	int		color;
	char	*comma;

	color = 0xFFFFFF;
	comma = ft_strchr(str, ',');
	if (comma)
	{
		comma++;
		if (*comma == '0' && *(comma + 1) == 'x')
			color = ft_atoi_base(comma + 2, 16);
	}
	return (color);
}

int	fill_points(t_map *map, char *line, int j)
{
	char	**split;
	int		i;

	split = ft_split(line, ' ');
	if (!split)
		return (0);
	i = 0;
	while (split[i] && i < map->width)
	{
		map->points[j][i].x = i;
		map->points[j][i].y = j;
		map->points[j][i].z = ft_atoi(split[i]);
		map->points[j][i].color = get_color(split[i]);
		free(split[i]);
		i++;
	}
	free(split[i]);
	free(split);
	return (1);
}

t_map	*read_map(char *filename)
{
	t_map	*map;
	int		fd;
	int		check;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (cleaner(map));
	check = get_map_data(map, fd);
	if (map->width <= 0 || map->height <= 0 || check == 0)
		return (cleaner(map));
	close(fd);
	if (allocate_points(map) == 0)
		return (cleaner(map));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (cleaner(map));
	if (update_map(map, fd) == 0)
		return (cleaner(map));
	close(fd);
	return (map);
}
