/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:50:21 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 10:50:21 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_linux/mlx.h"
#include "fdf.h"
#include <math.h>

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bit_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	isometric_projection(float *x, float *y, float z)
{
	float	previous_x;
	float	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.5);
	*y = (previous_x + previous_y) * sin(0.5) - (z / 3);
}

void	transform_point(t_point *p, t_data *data)
{
	float	x;
	float	y;
	float	z;

	x = p->x * data->scale;
	y = p->y * data->scale;
	z = p->z * data->scale;
	isometric_projection(&x, &y, z);
	p->x = x + data->shift_x;
	p->y = y + data->shift_y;
}

void	draw_width(t_data *data, t_point current, int y)
{
	int		x;
	t_point	right;
	t_point	down;

	x = 0;
	while (x < data->map->width)
	{
		current = data->map->points[y][x];
		transform_point(&current, data);
		if (x < data->map->width - 1)
		{
			right = data->map->points[y][x + 1];
			transform_point(&right, data);
			draw_line(data, current, right);
		}
		if (y < data->map->height - 1)
		{
			down = data->map->points[y + 1][x];
			transform_point(&down, data);
			draw_line(data, current, down);
		}
		x++;
	}
}

void	draw(t_data *data)
{
	int		y;
	t_point	current;

	y = 0;
	while (y < data->map->height)
	{
		draw_width(data, current, y);
		y++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
