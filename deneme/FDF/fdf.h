#ifndef FDF_H
#define FDF_H

#include <minilibx-linux/mlx.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

typedef struct s_point {
    int x;
    int y;
    int z;
} t_point;

typedef struct s_fdf {
    void *mlx_ptr;
    void *win_ptr;
    t_point **points;
    int width;
    int height;
} t_fdf;

void    parse_file(char *filename, t_fdf *fdf);
void    render(t_fdf *fdf);
void    free_fdf(t_fdf *fdf);

#endif