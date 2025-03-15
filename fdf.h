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
# define SHIFT_X WIDTH / 2
# define SHIFT_Y HEIGHT / 2

typedef struct s_point
{
	float x;
	float y;
	float z;
	int color;
} t_point;

typedef struct s_map
{
	int width;
	int height;
	t_point **points;
} t_map;

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

typedef struct s_data
{
	void *mlx;
	void *win;
	t_img img;
	t_map *map;
	float angle_x;
	float angle_y;
	float angle_z;
	float scale;
	int shift_x;
	int shift_y;
} t_data;

// Function prototypes
void    draw(t_data *data);
t_map   *read_map(char *filename);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    free_map(t_map *map);
void    isometric_projection(float *x, float *y, float z);
int     handle_key(int keycode, t_data *data);
int     handle_mouse(int button, int x, int y, t_data *data);
void    init_data(t_data *data);
void    *ft_memset(void *b, int c, size_t len);
char    **ft_split(char const *s, char c);
char    *get_next_line(int fd);
int     ft_atoi_base(char *str, int base);
char    *ft_strchr(const char *s, int c);
int     ft_atoi(char *str);
float   get_max_height(t_map *map);
float   get_min_height(t_map *map);


#endif