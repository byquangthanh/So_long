/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:32 by quanguye          #+#    #+#             */
/*   Updated: 2024/06/27 20:29:33 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img;
	void	*floor_img;
	void	*player_img;
	void	*wall_img;
	void	*collectible_img;
	void	*exit_img;

}	t_data;

typedef struct c_data
{
	int		exit;
	int		player;
	int		rows;
	int		cols;
	int		collectible;
}	t_sdata;

void	load_images(t_data *data);
int		ft_printf(const char *format, ...);
int		handle_close(t_data *data);
int		handle_keypress(int keysym, t_data *data);
void	verify_map(char *file);
char	*get_next_line(int fd);
int		ft_strlen(const char *s);
void	error_and_exit(char *error_message);
void	free_map_memory(char **map, int rows);

#endif
