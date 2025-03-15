#include "fdf.h"

static int count_words(char *line, char delimiter)
{
    int count = 0;
    int in_word = 0;

    while (*line)
    {
        if (*line != delimiter && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*line == delimiter)
            in_word = 0;
        line++;
    }
    return (count);
}

static int get_color(char *str)
{
    int color;
    char *comma;

    color = 0xFFFFFF;  // Default white color
    comma = ft_strchr(str, ',');
    if (comma)
    {
        comma++;
        if (*comma == '0' && *(comma + 1) == 'x')
            color = ft_atoi_base(comma + 2, 16);
    }
    return (color);
}

static void fill_points(t_map *map, char *line, int y)
{
    char **split;
    int x;

    split = ft_split(line, ' ');
    if (!split)
        return;
    x = 0;
    while (split[x] && x < map->width)
    {
        map->points[y][x].x = x;
        map->points[y][x].y = y;
        map->points[y][x].z = ft_atoi(split[x]);
        map->points[y][x].color = get_color(split[x]);
        free(split[x]);
        x++;
    }
    free(split[x]);
    free(split);
}

t_map *read_map(char *filename)
{
    t_map *map;
    int fd;
    char *line;
    int y;

    map = (t_map *)malloc(sizeof(t_map));
    if (!map)
        return (NULL);
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        free(map);
        return (NULL);
    }
    
    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        free(map);
        return (NULL);
    }
    
    map->width = count_words(line, ' ');
    map->height = 1;  // İlk satırı sayıyoruz
    free(line);
    while ((line = get_next_line(fd)))
    {
        if (count_words(line, ' ') > 0)
            map->height++;
        free(line);
    }
    
    close(fd);
    if (map->width <= 0 || map->height <= 0)
    {
        free(map);
        return (NULL);
    }
    
    map->points = (t_point **)malloc(sizeof(t_point *) * map->height);
    if (!map->points)
    {
        free(map);
        return (NULL);
    }
    
    for (y = 0; y < map->height; y++)
    {
        map->points[y] = (t_point *)malloc(sizeof(t_point) * map->width);
        if (!map->points[y])
        {
            while (--y >= 0)
                free(map->points[y]);
            free(map->points);
            free(map);
            return (NULL);
        }
    }
    
    fd = open(filename, O_RDONLY);
    if (fd < 0)
    {
        for (y = 0; y < map->height; y++)
            free(map->points[y]);
        free(map->points);
        free(map);
        return (NULL);
    }
    
    y = 0;
    while ((line = get_next_line(fd)))
    {
        if (count_words(line, ' ') > 0)
        {
            fill_points(map, line, y++);
        }
        free(line);
    }
    close(fd);
    
    return (map);
}