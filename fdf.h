/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mayilmaz <mayilmaz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 22:59:29 by mayilmaz          #+#    #+#             */
/*   Updated: 2025/03/04 22:17:30 by mayilmaz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef FDF_H

#define FDF_H

#include "get_next/get_next_line.h"
#include "minilibx-linux/mlx.h"
# define WIDTH 1500
# define HEIGHT 900
typedef struct s_mlx
{
	void	*begin;
	void	*img;
	void	*win;
	char	*data;
	int		bit;
	int		len;
	int		check;
	int		pixel;
} t_mlx;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	unsigned int color;
	
} t_point;

typedef struct s_map
{
	int		col_len;
	int		row_len;
	char	**row;
	char	**map;
} t_map;


char	**ft_split(char const *s, char c);

#endif