CC = gcc
CFLAGS = -Wall -Wextra -Werror
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx_linux
MLX = $(MLX_DIR)/libmlx.a

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(MLX_DIR) -O3 -c $< -o $@

all: $(FT_PRINTF) $(LIBFT) $(MLX) so_long

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

so_long: so_long.o $(LIBFT) $(FT_PRINTF) $(MLX)
	$(CC) $(CFLAGS) -o so_long so_long.o -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -L$(MLX_DIR) -lft -lftprintf -lmlx -lXext -lX11

so_long.o: so_long.c
	$(CC) $(CFLAGS) -Wno-unused-but-set-variable -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(MLX_DIR) -c so_long.c

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f *.o *~

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean  # Assuming mlx_linux doesn't have a fclean
	rm -f so_long

re: fclean all
