#include "fdf.h"

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
    {
        dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void isometric_projection(float *x, float *y, float z)
{
    float previous_x = *x;
    float previous_y = *y;
    
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = (previous_x + previous_y) * sin(0.523599) - z;
}

void draw_line(t_data *data, t_point start, t_point end)
{
    float delta_x = end.x - start.x;
    float delta_y = end.y - start.y;
    float pixel_x = start.x;
    float pixel_y = start.y;
    float pixel_count = fmax(fabs(delta_x), fabs(delta_y));
    
    if (pixel_count == 0)
        return;
        
    delta_x /= pixel_count;
    delta_y /= pixel_count;
    
    while (pixel_count > 0)
    {
        if (pixel_x >= 0 && pixel_x < WIDTH && pixel_y >= 0 && pixel_y < HEIGHT)
        {
            my_mlx_pixel_put(&data->img, pixel_x, pixel_y, start.color);
        }
        pixel_x += delta_x;
        pixel_y += delta_y;
        pixel_count--;
    }
}

void transform_point(t_point *p, t_data *data)
{
    float x = p->x * data->scale;
    float y = p->y * data->scale;
    float z = p->z * data->scale;

    isometric_projection(&x, &y, z);
    
    p->x = x + data->shift_x;
    p->y = y + data->shift_y;
}

void draw(t_data *data)
{
    int x, y;
    t_point current, right, down;

    ft_memset(data->img.addr, 0, WIDTH * HEIGHT * (data->img.bits_per_pixel / 8));

    for (y = 0; y < data->map->height; y++)
    {
        for (x = 0; x < data->map->width; x++)
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
        }
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}