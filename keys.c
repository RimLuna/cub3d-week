#include "cub3d.h"

int		key_pressed(int key, t_game *game)
{
	if (key == KEY_ESC)
		quit(game, SUCCESS);
	else if (key == KEY_A)
		game->ctrls.a = TRUE;
	else if (key == KEY_D)
		game->ctrls.d = TRUE;
	else if (key == KEY_W)
		game->ctrls.w = TRUE;
	else if (key == KEY_S)
		game->ctrls.s = TRUE;
	else if (key == KEY_LEFT)
		game->ctrls.left = TRUE;
	else if (key == KEY_RIGHT)
		game->ctrls.right = TRUE;
	return (TRUE);
}


int		key_released(int key, t_game *game)
{
	if (key == KEY_A)
		game->ctrls.a = FALSE;
	else if (key == KEY_D)
		game->ctrls.d = FALSE;
	else if (key == KEY_W)
		game->ctrls.w = FALSE;
	else if (key == KEY_S)
		game->ctrls.s = FALSE;
	else if (key == KEY_LEFT)
		game->ctrls.left = FALSE;
	else if (key == KEY_RIGHT)
		game->ctrls.right = FALSE;
	return (TRUE);
}

