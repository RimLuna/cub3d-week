/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:41 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:10:52 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool		is_hit(t_game *game, t_dda *ddata, t_text *texture, double ray[2])
{
	if (ddata->side_dist[0] < ddata->side_dist[1])
	{
		ddata->side_dist[0] += ddata->delta_dist[0];
		ddata->map_pos[0] += ddata->step[0];
		texture->side = ray[0] > 0 ? N : S;
	}
	else
	{
		ddata->side_dist[1] += ddata->delta_dist[1];
		ddata->map_pos[1] += ddata->step[1];
		texture->side = ray[1] > 0 ? E : W;
	}
	return (game->map[ddata->map_pos[0]][ddata->map_pos[1]] == 1);
}

void		draw_line(int x, t_game *game, t_text the_texture)
{
	int		j;
	int		color;
	t_img	texture_img;
	int		start;
	int		end;

	start = game->scr_h / 2 - the_texture.line_height / 2;
	end = game->scr_h / 2 + the_texture.line_height / 2;
	texture_img = game->textures[the_texture.side];
	j = 0;
	while (j < (start < 0 ? 0 : start))
		put_it(game->screen, x, j++, game->color_ceil);
	while (j < (end >= game->scr_h ? game->scr_h - 1 : end))
	{
		color = texture_to_color(texture_img, the_texture.wall_x,
			((j - start) * 1.0) / (end - start));
		put_it(game->screen, x, j++, color);
	}
	while (j < game->scr_h)
		put_it(game->screen, x, j++, game->color_floor);
}

void		wallz(t_game *game)
{
	double		camera_x;
	int			i;
	double		ray[2];

	i = 0;
	while (i < game->scr_w)
	{
		camera_x = 2.0 * i / game->scr_w - 1;
		ray[0] = game->dir[0] + game->cam_plane[0] * camera_x;
		ray[1] = game->dir[1] + game->cam_plane[1] * camera_x;
		dda(game, ray, i);
		i++;
	}
}

void		draw(t_game *game)
{
	wallz(game);
	spr1tes(game);
	if (game->save)
		ugh_bmp(game);
	else
		mlx_put_image_to_window(game->mlx.ptr, game->mlx.win,
			game->screen.ptr, 0, 0);
}
