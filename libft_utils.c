/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 23:59:24 by marvin            #+#    #+#             */
/*   Updated: 2025/03/20 23:59:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	ft_negative(char *a1, int *sw)
{
	int	j;
	int	ops;

	j = 0;
	ops = 1;
	while ((a1[j] >= 9 && a1[j] <= 13) || a1[j] == 32)
	{
		j++;
	}
	if (a1[j] == 45 || a1[j] == 43)
	{
		if (a1[j] == 45)
			ops *= -1;
		j++;
	}
	*sw = j;
	return (ops);
}

int	ft_atoi(char *str)
{
	int			i;
	long int	number;
	int			negative;
	char		*s1;

	s1 = (char *)str;
	number = 0;
	negative = ft_negative(s1, &i);
	while (s1[i] >= 48 && s1[i] <= 57)
	{
		number *= 10;
		number += s1[i] - 48;
		i++;
	}
	number *= negative;
	return (number);
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
	map->width = word_count(line, ' ');
	map->height = 1;
	free(line);
	while ((line = get_next_line(fd)))
	{
		if (word_count(line, ' ') > 0)
			map->height++;
		free(line);
	}
	return (1);
}

int	update_map(t_map *map, int fd)
{
	char	*line;
	int		y;

	y = 0;
	while ((line = get_next_line(fd)))
	{
		if (count_words(line, ' ') > 0)
		{
			if (fill_points(map, line, y++) == 0)
			{
				free(line);
				return (0);
			}
		}
		free(line);
	}
	return (1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
