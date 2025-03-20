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
    int dx = abs((int)end.x - (int)start.x);
    int dy = -abs((int)end.y - (int)start.y);
    int sx = start.x < end.x ? 1 : -1;
    int sy = start.y < end.y ? 1 : -1;
    int err = dx + dy;
    int e2;
    int x = (int)start.x;
    int y = (int)start.y;

    while (1)
    {
        if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
        {
            my_mlx_pixel_put(&data->img, x, y, start.color);
        }
        
        if (x == (int)end.x && y == (int)end.y)
            break;
            
        e2 = 2 * err;
        if (e2 >= dy)
        {
            if (x == (int)end.x)
                break;
            err += dy;
            x += sx;
        }
        if (e2 <= dx)
        {
            if (y == (int)end.y)
                break;
            err += dx;
            y += sy;
        }
    }
}

void transform_point(t_point *p, t_data *data)
{
    float x = p->x * data->scale;
    float y = p->y * data->scale;
    float z = p->z * data->scale;
    
    // Apply height scaling factor to prevent extreme values
    if (z > HEIGHT)
        z = HEIGHT;
    else if (z < -HEIGHT)
        z = -HEIGHT;

    isometric_projection(&x, &y, z);
    
    p->x = x + data->shift_x;
    p->y = y + data->shift_y;
}

void calculate_map_boundaries(t_data *data, float *min_y, float *max_y)
{
    int x, y;
    t_point p;
    
    *min_y = HEIGHT;
    *max_y = -HEIGHT;
    
    for (y = 0; y < data->map->height; y++)
    {
        for (x = 0; x < data->map->width; x++)
        {
            p = data->map->points[y][x];
            
            // Temporarily transform to check boundaries without actually setting p
            float temp_x = p.x * data->scale;
            float temp_y = p.y * data->scale;
            float temp_z = p.z * data->scale;
            
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
    }
}

void adjust_shift_for_overflow(t_data *data)
{
    float min_y, max_y;
    
    calculate_map_boundaries(data, &min_y, &max_y);
    
    // Check if map overflows the window
    int top_overflow = 0;
    int bottom_overflow = 0;
    
    if (min_y < 0)
        top_overflow = -min_y;
    if (max_y > HEIGHT)
        bottom_overflow = max_y - HEIGHT;
    
    // If there's overflow, adjust shift_y
    if (top_overflow > 0)
    {
        data->shift_y += top_overflow + 50; // Add padding of 50 pixels
    }
    else if (bottom_overflow > 0)
    {
        data->shift_y -= bottom_overflow + 50; // Add padding of 50 pixels
    }
}

void    draw_width(t_data *data, t_point current, int y)
{
    int     x;
    t_point right;
    t_point down;

    x = 0;
    while( x < data->map->width)
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

void draw(t_data *data)
{
    int y;
    t_point current;

    // Adjust shift before drawing to prevent overflow
    adjust_shift_for_overflow(data);
    y = 0;
    while(y < data->map->height)
    {
        draw_width(data, current, y);
        y++;
    }
    mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
}
