#include "minilibx-linux/mlx.h"
#include <stdio.h>


int main()
{
	void	*atr;
	void	*str;
	void	*win;
	int		bit;
	int		len;
	int		check;
	char	*data;
	int		pixel;
	atr = mlx_init();

	win = mlx_new_window(atr, 1500, 900, "mahmut");
	str = mlx_new_image(atr, 1500, 900);
	data = mlx_get_data_addr(str, &bit, &len, &check);
	pixel = (985 * 4) + (370 * len);
	*(unsigned int *)(data + pixel) = 0xFFFFFF;
	pixel = (995 * 4) + (380 * len);
	*(unsigned int *)(data + pixel) = 0xFFFFFF;
	pixel = (995 * 4) + (353 * len);
	*(unsigned int *)(data + pixel) = 0xFFFFFF;
	pixel = (985 * 4) + (353 * len);
	*(unsigned int *)(data + pixel) = 0xFF0000;
	mlx_put_image_to_window(atr, win, str, 0, 0);
	mlx_loop (atr);
}
