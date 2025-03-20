#include "fdf.h"

void init_data(t_data *data)
{
    float scale_x;
    float scale_y;
    float map_width_iso;
    float map_height_iso;
    float center_x;
    float center_y;
    float max_height_diff;
    
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "FDF");
    data->img.img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
                                    &data->img.line_length, &data->img.endian);
    
    // Calculate maximum height difference
    max_height_diff = get_max_height(data->map) - get_min_height(data->map);
    
    // Calculate map dimensions after isometric projection
    map_width_iso = (data->map->width + data->map->height) * cos(0.523599); // 30 degrees in radians
    
    // Add height factor with a scaling factor to prevent overflow
    float height_factor = fmin(max_height_diff, max_height_diff * (WIDTH / (float)HEIGHT));
    map_height_iso = (data->map->width + data->map->height) * sin(0.523599) + height_factor;
    
    // Calculate scale to fit map in window with safe margins
    scale_x = (WIDTH * 0.7) / map_width_iso;
    scale_y = (HEIGHT * 0.7) / map_height_iso;
    data->scale = (scale_x < scale_y) ? scale_x : scale_y;
    
    // Calculate center point of the map
    center_x = (data->map->width - 1) / 2.0;
    center_y = (data->map->height - 1) / 2.0;
    
    // Calculate center point after isometric projection
    float iso_x = (center_x - center_y) * cos(0.523599);
    float iso_y = (center_x + center_y) * sin(0.523599);
    
    // Set shift values to center the map
    data->shift_x = SHIFT_X - (iso_x * data->scale);
    data->shift_y = SHIFT_Y - (iso_y * data->scale) + (HEIGHT * 0.1); // Move the map 20% down the screen
}

int handle_key(int keycode, t_data *data)
{
    if (keycode == 53 || keycode == 65307)  // ESC key
    {
        mlx_destroy_image(data->mlx, data->img.img);
        mlx_destroy_window(data->mlx, data->win);
        free_map(data->map);
        mlx_destroy_display(data->mlx);
        free(data->mlx);
        exit(0);
    }
    return (0);
}


int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    data.map = read_map(argv[1]);
    if (!data.map)
    {
        printf("Error: could not read the map\n");
        return (1);
    }

    init_data(&data);
    draw(&data);

    mlx_key_hook(data.win, handle_key, &data);
    mlx_loop(data.mlx);

    return (0);
}