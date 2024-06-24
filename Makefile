CC = cc
CFLAGS = -Wall -Wextra -Werror
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = mlx_linux
MLX = $(MLX_DIR)/libmlx.a
GNL_DIR = GNL

# Find all .c files in the current directory and GNL directory
SRC = $(wildcard *.c) $(wildcard $(GNL_DIR)/*.c)

# Replace .c with .o for all files found
OBJ = $(SRC:.c=.o)

# Additional include directories
INCLUDES = -I/usr/include -I$(MLX_DIR) -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)

# Flags for linking MLX and X11
MLX_FLAGS = -L$(MLX_DIR) -lmlx -L/usr/lib/X11 -lXext -lX11 -lm -lbsd

# Generic rule for compiling .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

all: $(FT_PRINTF) $(LIBFT) $(MLX) $(OBJ)
	$(CC) $(CFLAGS) -o so_long $(OBJ) $(MLX_FLAGS) -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lftprintf -lft

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX):
	$(MAKE) -C $(MLX_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ) *~

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f so_long

re: fclean all

.PHONY: all clean fclean re $(LIBFT) $(FT_PRINTF) $(MLX)
