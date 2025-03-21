/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 15:31:58 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 15:31:58 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	check_condition(int *err, int *x, int *y, t_draw_data *d)
{
	int	error2;

	error2 = 2 * (*err);
	if (error2 >= d->dy)
	{
		if (*x == d->end_x)
			return ;
		else
		{
			*err += d->dy;
			*x += d->sx;
		}
	}
	if (error2 <= d->dx)
	{
		if (*y == d->end_y)
			return ;
		else
		{
			*err += d->dx;
			*y += d->sy;
		}
	}
}

void	draw_line_worker(t_data *data, t_point start, t_draw_data d)
{
	int	x;
	int	y;
	int	err;

	x = (int)start.x;
	y = (int)start.y;
	err = d.dx + d.dy;
	while (1)
	{
		my_mlx_pixel_put(&data->img, x, y, start.color);
		check_condition(&err, &x, &y, &d);
		if (x == d.end_x && y == d.end_y)
			break ;
	}
}

void	draw_line(t_data *data, t_point start, t_point end)
{
	t_draw_data	d;

	d.dx = abs((int)end.x - (int)start.x);
	d.dy = -abs((int)end.y - (int)start.y);
	if (start.x < end.x)
		d.sx = 1;
	else
		d.sx = -1;
	if (start.y < end.y)
		d.sy = 1;
	else
		d.sy = -1;
	d.end_x = (int)end.x;
	d.end_y = (int)end.y;
	draw_line_worker(data, start, d);
}
