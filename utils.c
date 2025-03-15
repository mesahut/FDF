#include "fdf.h"

void free_map(t_map *map)
{
    int i;

    if (!map)
        return;
    if (map->points)
    {
        for (i = 0; i < map->height; i++)
        {
            if (map->points[i])
                free(map->points[i]);
        }
        free(map->points);
    }
    free(map);
}

int ft_atoi_base(char *str, int base)
{
    int result;
    int digit;

    result = 0;
    while (*str)
    {
        if (*str >= '0' && *str <= '9')
            digit = *str - '0';
        else if (*str >= 'a' && *str <= 'f')
            digit = *str - 'a' + 10;
        else if (*str >= 'A' && *str <= 'F')
            digit = *str - 'A' + 10;
        else
            break;
        result = result * base + digit;
        str++;
    }
    return (result);
}

char *ft_strchr(const char *s, int c)
{
    while (*s)
    {
        if (*s == (char)c)
            return ((char *)s);
        s++;
    }
    if ((char)c == '\0')
        return ((char *)s);
    return (NULL);
}

float get_max_height(t_map *map)
{
    int x;
    int y;
    float max_height;

    max_height = map->points[0][0].z;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->points[y][x].z > max_height)
                max_height = map->points[y][x].z;
            x++;
        }
        y++;
    }
    return (max_height);
}

float get_min_height(t_map *map)
{
    int x;
    int y;
    float min_height;

    min_height = map->points[0][0].z;
    y = 0;
    while (y < map->height)
    {
        x = 0;
        while (x < map->width)
        {
            if (map->points[y][x].z < min_height)
                min_height = map->points[y][x].z;
            x++;
        }
        y++;
    }
    return (min_height);
}
