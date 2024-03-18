CC = gcc
CFLAGS = -Wall -Wextra -Werror
FT_PRINTF_DIR = ft_printf
FT_PRINTF = $(FT_PRINTF_DIR)/libftprintf.a
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

all:$(FT_PRINTF) $(LIBFT) so_long

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(FT_PRINTF):
	$(MAKE) -C $(FT_PRINTF_DIR)

so_long: so_long.o $(LIBFT) $(FT_PRINTF)
	$(CC) $(CFLAGS) -o so_long so_long.o -L$(LIBFT_DIR) -L$(FT_PRINTF_DIR) -lft -lftprintf

so_long.o: so_long.c
	$(CC) $(CFLAGS) -c so_long.c

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(FT_PRINTF_DIR) clean
	rm -f so_long.o

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(FT_PRINTF_DIR) fclean
	rm -f so_long

re: fclean all
