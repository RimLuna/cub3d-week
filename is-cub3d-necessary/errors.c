#include "cub3d.h"

void				quit(t_game *game, int ret)
{
	free_game(game);
	exit(ret);
}

void				parserror(t_game *game, char *msg)
{
	if (game->error)
		return ;
	write(1, "Error:\n", 7);
	write(1, msg, ft_strlen(msg));
	game->error = 1;
}
