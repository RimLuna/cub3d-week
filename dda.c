/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:03:53 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:04:30 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_dda		init_dda(t_game *game, double ray[2])
{
	t_dda	ddata;

	ddata.delta_dist[0] = fabs(1.0 / ray[0]);
	ddata.delta_dist[1] = fabs(1.0 / ray[1]);
	ddata.map_pos[0] = floor(game->pos[0]);
	ddata.map_pos[1] = floor(game->pos[1]);
	ddata.step[0] = (ray[0] < 0) ? -1 : 1;
	ddata.step[1] = (ray[1] < 0) ? -1 : 1;
	ddata.side_dist[0] = (ray[0] < 0)
		? (game->pos[0] - ddata.map_pos[0]) * ddata.delta_dist[0]
		: (ddata.map_pos[0] + 1.0 - game->pos[0]) * ddata.delta_dist[0];
	ddata.side_dist[1] = (ray[1] < 0)
		? (game->pos[1] - ddata.map_pos[1]) * ddata.delta_dist[1]
		: (ddata.map_pos[1] + 1.0 - game->pos[1]) * ddata.delta_dist[1];
	return (ddata);
}

void		dda(t_game *game, double ray[2], int i)
{
	t_bool		hit;
	t_dda		ddata;
	t_text		texture;

	hit = FALSE;
	ddata = init_dda(game, ray);
	while (!hit)
		hit = is_hit(game, &ddata, &texture, ray);
	texture.wall_dist = (texture.side == N || texture.side == S)
		? (ddata.map_pos[0] - game->pos[0] + (1 - ddata.step[0]) / 2) / ray[0]
		: (ddata.map_pos[1] - game->pos[1] + (1 - ddata.step[1]) / 2) / ray[1];
	game->z_buffer[i] = texture.wall_dist;
	texture.wall_x = (texture.side == N || texture.side == S)
		? game->pos[1] + texture.wall_dist * ray[1]
		: game->pos[0] + texture.wall_dist * ray[0];
	texture.wall_x -= floor(texture.wall_x);
	texture.line_height = texture.wall_dist > 0
		? game->scr_h / texture.wall_dist : 2147483647;
	draw_line(i, game, texture);
}
