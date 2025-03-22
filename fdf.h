/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:09:14 by marvin            #+#    #+#             */
/*   Updated: 2025/03/21 00:09:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080

#include <stdio.h>
typedef struct s_point
{
	float	x;
	float	y;
	int		z;
	int		color;
}	t_point;

typedef struct s_draw_data
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	end_x;
	int	end_y;
}	t_draw_data;

typedef struct s_map
{
	int		width;
	int		height;
	t_point	**points;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bit_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
	float	scale;
	int		shift_x;
	int		shift_y;
	int		a;
}	t_data;

void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_data *data, t_point start, t_point end);
int		fill_points(t_map *map, char *line, int j);
int		word_count(const char *s, char c);
int		handle_key(int keycode, t_data *data);
int		ft_atoi_base(char *str, int base);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *s, int c);
int		get_map_data(t_map *map, int fd);
int		update_map(t_map *map, int fd);
int		allocate_points(t_map *map);
int		close_window(t_data *data);
t_map	*read_map(char *filename);
void	*cleaner(t_map *map);
void	draw(t_data *data);
int		ft_atoi(char *str);
void	ft_putstr(char *s);

#endif