#include "cub3d.h"
#include <stdio.h>

t_bool	camera(t_game *game)
{
	double		camera_x;
	double		plane_center_dist;

	printf("%f %f\n", game->dir[0], game->dir[1]);
	v_scale(2, game->dir, game->ray);
	printf("%f %f\n", game->ray[0], game->ray[1]);
	return (TRUE);
}

int		main(int ac, char **av)
{
	t_game		*game;
	if (!(game = game_init(ac, av)))
		return (ERROR);
	camera(game);
	quit(game, SUCCESS);
	return (SUCCESS);
}