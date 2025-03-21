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

# include "minilibx_linux/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "get_next_line.h"

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
	int		color;
}	t_point;

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
	int		bits_per_pixel;
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
}	t_data;

void	draw(t_data *data);
t_map	*read_map(char *filename);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	free_map(t_map *map);
void	isometric_projection(float *x, float *y, float z);
int		handle_key(int keycode, t_data *data);
void	init_data(t_data *data);
char	**ft_split(char const *s, char c);
char	*get_next_line(int fd);
int		ft_atoi_base(char *str, int base);
char	*ft_strchr(const char *s, int c);
int		ft_atoi(char *str);
int		get_map_data(t_map *map, int fd);
float	get_max_height(t_map *map);
float	get_min_height(t_map *map);
int		allocate_points(t_map *map);
int		update_map(t_map *map, int fd);
int		word_count(const char *s, char c);
int		fill_points(t_map *map, char *line, int j);
int		count_words(char *line, char delimiter);
void	*cleaner(t_map *map);
void	ft_putstr(char *s);
void	calculate_shift(t_data *data);
int		close_window(t_data *data);
void	calculate_scale(t_data *data, float scale_x, float scale_y);

#endif