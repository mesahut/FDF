NAME = fdf

SRCS = draw.c draw_line.c main.c read_map.c utils.c utils_two.c libft_utils.c ft_split.c get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -Lminilibx_linux -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS)
	make -C minilibx_linux
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Iminilibx_linux -c $< -o $@

clean:
	make -C ./minilibx_linux clean
	rm -f $(OBJS)

fclean: clean
	make -C ./minilibx_linux clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re