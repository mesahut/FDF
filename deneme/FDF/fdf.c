#include "fdf.h"

void free_points(t_point **points, int height) {
    for (int i = 0; i < height; i++) {
        free(points[i]);
    }
    free(points);
}

void parse_file(char *filename, t_fdf *fdf) {
    int fd;
    char *line;
    char **split_line;
    int x, y;

    fdf->height = 0;
    fdf->width = 0;

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // First pass: Count the number of lines and determine width
    while ((line = get_next_line(fd))) {
        split_line = ft_split(line, ' '); // Split line by spaces
        if (fdf->width == 0) {
            while (split_line[fdf->width]) {
                fdf->width++; // Count the number of points in the first line
            }
        }
        fdf->height++; // Increment height for each line
        free(line);
        free(split_line);
    }
    close(fd);

    // Allocate memory for points
    fdf->points = malloc(sizeof(t_point *) * fdf->height);
    for (y = 0; y < fdf->height; y++) {
        fdf->points[y] = malloc(sizeof(t_point) * fdf->width);
    }

    // Second pass: Read the file again to populate points
    fd = open(filename, O_RDONLY);
    y = 0;
    while ((line = get_next_line(fd))) {
        split_line = ft_split(line, ' '); // Split line by spaces
        for (x = 0; x < fdf->width; x++) {
            fdf->points[y][x].x = x; // Set x coordinate
            fdf->points[y][x].y = y; // Set y coordinate
            fdf->points[y][x].z = atoi(split_line[x]); // Set z coordinate
        }
        free(line);
        free(split_line);
        y++;
    }
    close(fd);
}

// Function to draw a line between two points
void draw_line(t_point p1, t_point p2, t_fdf *fdf) {
    int dx = abs(p2.x - p1.x);
    int dy = abs(p2.y - p1.y);
    int sx = (p1.x < p2.x) ? 1 : -1;
    int sy = (p1.y < p2.y) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        mlx_pixel_put(fdf->mlx_ptr, fdf->win_ptr, p1.x, p1.y, 0xFFFFFF); // Draw pixel
        if (p1.x == p2.x && p1.y == p2.y) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            p1.x += sx;
        }
        if (err2 < dx) {
            err += dx;
            p1.y += sy;
        }
    }
}

// Function to render the wireframe model
void render(t_fdf *fdf) {
    for (int y = 0; y < fdf->height; y++) {
        for (int x = 0; x < fdf->width; x++) {
            // Draw lines to the right
            if (x < fdf->width - 1) {
                draw_line(fdf->points[y][x], fdf->points[y][x + 1], fdf);
            }
            // Draw lines downwards
            if (y < fdf->height - 1) {
                draw_line(fdf->points[y][x], fdf->points[y + 1][x], fdf);
            }
        }
    }
}

int main(int argc, char **argv) {
    t_fdf fdf;

    if (argc != 2) {
        write(1, "Usage: ./fdf <filename>\n", 24);
        return (1);
    }
    parse_file(argv[1], &fdf);
    fdf.mlx_ptr = mlx_init();
    fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 800, 600, "FDF");
    render(&fdf);
    mlx_loop(fdf.mlx_ptr);
    free_fdf(&fdf);
    return (0);
}