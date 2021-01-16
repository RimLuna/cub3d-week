#include "cub3d.h"
#include <stdio.h>

t_bool	move(t_game *game)
{
	double		dx;
	double		dy;
	double		speed;

	speed = 0.15;
	if (!(game->ctrls.w || game->ctrls.s || game->ctrls.a || game->ctrls.d))
		return (FALSE);
	if (game->ctrls.w || game->ctrls.s)
	{
		dx = game->dir[0] * (game->ctrls.w ? speed : -speed);
		dy = game->dir[1] * (game->ctrls.w ? speed : -speed);
	}
	else
	{
		dx = game->cam_plane[0] * (game->ctrls.d ? speed : -speed);
		dy = game->cam_plane[1] * (game->ctrls.d ? speed : -speed);
	}
	if (game->map[(int)(game->pos[0] + dx)][(int)(game->pos[1] + dy)] != 1)
	{
		game->pos[0] += dx;
		game->pos[1] += dy;
	}
	return (TRUE);
	
}

t_bool	rotate(t_game *game)
{
	double	tmp;
	double	angle;

	if (!game->ctrls.right && !game->ctrls.left)
		return (FALSE);
	angle = (game->ctrls.left) ? M_PI / 100 : -M_PI / 100;
	tmp = game->dir[0];
	game->dir[0] = tmp * cos(angle) - game->dir[1] * sin(angle);
	game->dir[1] = tmp * sin(angle) + game->dir[1] * cos(angle);
	tmp = game->cam_plane[0];
	game->cam_plane[0] = tmp * cos(angle) - game->cam_plane[1] * sin(angle);
	game->cam_plane[1] = tmp * sin(angle) + game->cam_plane[1] * cos(angle);
	return (TRUE);
}

int		game_loop(t_game *game)
{
	t_bool		huh;

	huh = move(game);
	huh = rotate(game) || huh;
	if (huh)
		draw(game);
	return (TRUE);
}

int		main(int ac, char **av)
{
	t_game		*game;
	if (!(game = game_init(ac, av)))
		return (ERROR);
	draw(game);
	// printf("%d %f %f %f %f\n", game->save, game->pos[0], game->pos[1], game->cam_plane[0], game->cam_plane[1]);
	// draw(game);
	mlx_hook(game->mlx.win, 2, 1L << 0, &key_pressed, game);
	mlx_hook(game->mlx.win, 3, 1L << 1, &key_released, game);
	mlx_hook(game->mlx.win, 17, 0, quit, game);
	mlx_loop_hook(game->mlx.ptr, game_loop, game);
	mlx_loop(game->mlx.ptr);
	quit(game, SUCCESS);
	return (SUCCESS);
}