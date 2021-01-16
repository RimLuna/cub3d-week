#include "cub3d.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_game		*game;
	if (!(game = game_init(ac, av)))
		return (ERROR);
	quit(game, SUCCESS);
	return (SUCCESS);
}