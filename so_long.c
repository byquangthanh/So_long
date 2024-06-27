/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quanguye <quanguye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 13:28:28 by quanguye          #+#    #+#             */
/*   Updated: 2024/06/26 13:39:21 by quanguye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
-------------GOALS-------------
1. Use MiniLibX
2. Program has to take as parameter a map description file ending with the .ber
extension

-------------GAME--------------
1. Player has to collect every collectible and then reach the exit using
shortest path possible
2. W, A, S, D to move
3. Directions: up, down, left, right
4. Not move into walls
5. Number of movements must be displayed in the shell
6. 2D view
7. Doesnt have to be real time

-------------GRAPHIC MANAGEMENT---------------
1. Display the image in a window DONE
2. Management of window must remain smooth (resizing, minimizing, etc)
3. ESC to close the window and quit the program DONE
4. Clicking on cross on window's frame must close the window and quit the DONE
5. Use images of MinilibX

-------------MAP MANAGEMENT---------------------
1. Map must be composed of only 5 different characters:
	- 0: empty space
	- 1: wall
	- C: collectible
	- E: exit
	- P: player
2. The map has to be constructed with 3 components: walls,
	collectibles and free space
3. Map must contain 1 exit, at leat 1 collectible and 1 starting position
4. Map has to be rectangular
5. Map must be closed/surrounded by walls, if not, the program must return
6. Check if the map is valid
7. Parse any kind of map, as long as it respects the rules
8. example of minimal .ber map:
1111111111111111111111111111111111
1E0000000000000C00000C000000000001
1010010100100000101001000000010101
1010010010101010001001000000010101
1P0000000C00C0000000000000000000C1
1111111111111111111111111111111111
9. If any misconfiguration of the map is detected, the program must return
	"Error\n" followed by an explicit error message of
	your choice
*/

#include "so_long.h"

int	main(int ac, char **av)
{

	if (ac != 2)
	{
		ft_printf("Error\nUsage: ./program map\n");
		return (1);
	}
	verify_map(av[1]);

	return (0);
}

// 119 W
// 97 A
// 115 S
// 100 D
