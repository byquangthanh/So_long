CC = cc
CFLAGS = -Wall -Wextra -Werror
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
MLX_DIR = MLX42
MLX = $(MLX_DIR)/libmlx42.a
GNL_DIR = GNL

# Find all .c files in the current directory and GNL_DIR
SRC = $(wildcard *.c) $(wildcard $(GNL_DIR)/*.c)

# Replace .c with .o for all files found
OBJ = $(SRC:.c=.o)

# Additional include directories
INCLUDES = -I/usr/include -I$(MLX_DIR)/include -I$(LIBFT_DIR) -I$(FT_PRINTF_DIR) -I$(GNL_DIR)

# Flags for linking MLX42 and its dependencies
MLX_FLAGS = -L$(MLX_DIR) -lmlx42 -ldl -lglfw -pthread -lm

# Generic rule for compiling .c to .o
%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -O3 -c $< -o $@

all: $(FT_PRINTF) $(LIBFT) $(MLX) so_long

so_long: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(MLX_FLAGS) -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lftprintf -lft

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

$(MLX):
	mkdir -p $(MLX_DIR)
	cd $(MLX_DIR) && cmake . && make

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
