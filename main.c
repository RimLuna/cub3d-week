/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:50 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/24 18:43:21 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			exit_hook(t_game *game)
{
	die(game, SUCCESS);
	return (TRUE);
}

t_bool		move(t_game *game)
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

t_bool		rotate(t_game *game)
{
	double	dir;
	double	angle;

	if (!game->ctrls.right && !game->ctrls.left)
		return (FALSE);
	angle = (game->ctrls.left) ? M_PI / 100 : -M_PI / 100;
	dir = game->dir[0];
	game->dir[0] = dir * cos(angle) - game->dir[1] * sin(angle);
	game->dir[1] = dir * sin(angle) + game->dir[1] * cos(angle);
	dir = game->cam_plane[0];
	game->cam_plane[0] = dir * cos(angle) - game->cam_plane[1] * sin(angle);
	game->cam_plane[1] = dir * sin(angle) + game->cam_plane[1] * cos(angle);
	return (TRUE);
}

t_bool		this_game_is_stupid(t_game *game)
{
	t_bool		huh;

	huh = move(game);
	huh = rotate(game) | huh;
	if (huh)
		draw(game);
	return (TRUE);
}

int			main(int ac, char **av)
{
	t_game		*game;

	if (!(game = game_init(ac, av)))
		return (ERROR);
	draw(game);
	if (game->save)
		die(game, SUCCESS);
	mlx_hook(game->mlx.win, 2, 0, &key_pressed, game);
	mlx_hook(game->mlx.win, 3, 0, &key_released, game);
	mlx_hook(game->mlx.win, 17, 0, &exit_hook, game);
	mlx_loop_hook(game->mlx.ptr, this_game_is_stupid, game);
	mlx_loop(game->mlx.ptr);
	die(game, SUCCESS);
	return (SUCCESS);
}
