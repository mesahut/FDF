/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:31:33 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 15:31:33 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	point_boundaries(t_point p, t_data *data, float *min_y, float *max_y)
{
	float	temp_x;
	float	temp_y;
	float	temp_z;

	temp_x = p.x * data->scale;
	temp_y = p.y * data->scale;
	temp_z = p.z * data->scale;
	if (temp_z > HEIGHT)
		temp_z = HEIGHT;
	else if (temp_z < -HEIGHT)
		temp_z = -HEIGHT;
	isometric_projection(&temp_x, &temp_y, temp_z);
	temp_y += data->shift_y;
	if (temp_y < *min_y)
		*min_y = temp_y;
	if (temp_y > *max_y)
		*max_y = temp_y;
}

void	calculate_map_boundaries(t_data *data, float *min_y, float *max_y)
{
	int		x;
	int		y;
	t_point	p;

	*min_y = HEIGHT;
	*max_y = -HEIGHT;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			p = data->map->points[y][x];
			point_boundaries(p, data, min_y, max_y);
			x++;
		}
		y++;
	}
}

void	adjust_shift(t_data *data)
{
	float	min_y;
	float	max_y;
	int		bottom_overflow;
	int		top_overflow;

	calculate_map_boundaries(data, &min_y, &max_y);
	top_overflow = 0;
	bottom_overflow = 0;
	if (min_y < 0)
		top_overflow = -min_y;
	if (max_y > HEIGHT)
		bottom_overflow = max_y - HEIGHT;
	if (top_overflow > 0)
		data->shift_y += top_overflow + 50;
	else if (bottom_overflow > 0)
		data->shift_y -= bottom_overflow + 50;
}
