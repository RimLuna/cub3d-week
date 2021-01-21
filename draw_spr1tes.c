/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_spr1tes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:00:12 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:03:25 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		calculate_each_distance(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->nb_sprites)
	{
		game->sprites[i].distance =
			pow(game->pos[0] - game->sprites[i].pos[0], 2)
			+ pow(game->pos[1] - game->sprites[i].pos[1], 2);
		i++;
	}
}

void		sort_sprites(t_game *game)
{
	int			i;
	int			j;
	t_sprite	for_swap;

	i = 0;
	while (i < game->nb_sprites)
	{
		j = 0;
		while (j < game->nb_sprites - i - 1)
		{
			if (game->sprites[i].distance < game->sprites[i + 1].distance)
			{
				for_swap = game->sprites[i];
				game->sprites[i] = game->sprites[i + 1];
				game->sprites[i + 1] = for_swap;
			}
			j++;
		}
		i++;
	}
}

void		ver_sprite(t_game *game, t_sprited sprited,
	int i, int sprite_box_x[2])
{
	int		sprite_box_y[2];
	int		j;
	int		color;

	sprite_box_y[0] = game->scr_h / 2 - sprited.size / 2;
	sprite_box_y[1] = game->scr_h / 2 + sprited.size / 2;
	j = (sprite_box_y[0] < 0) ? 0 : sprite_box_y[0];
	while (j < (sprite_box_y[1] >= game->scr_h
		? game->scr_h - 1 : sprite_box_y[1]))
	{
		color = texture_to_color(game->sprites[sprited.i].texture,
			((i - sprite_box_x[0]) * 1.0) / (sprite_box_x[1] - sprite_box_x[0]),
			((j - sprite_box_y[0]) * 1.0)
				/ (sprite_box_y[1] - sprite_box_y[0]));
		if (color != 0)
			put_it(game->screen, i, j, color);
		j++;
	}
}

void		draw_sprite(t_game *game, t_sprited sprited)
{
	int		sprite_box_x[2];
	int		i;

	sprite_box_x[0] = sprited.x - sprited.size / 2;
	sprite_box_x[1] = sprited.x + sprited.size / 2;
	i = (sprite_box_x[0] < 0) ? 0 : sprite_box_x[0];
	while (i <= (sprite_box_x[1] >= game->scr_w
		? game->scr_w - 1 : sprite_box_x[1]))
	{
		if (sprited.transform[1] > 0
			&& sprited.transform[1] < game->z_buffer[i])
			ver_sprite(game, sprited, i, sprite_box_x);
		i++;
	}
}

void		spr1tes(t_game *game)
{
	t_sprited		sprited;
	double			s_pos[2];
	double			inv_det;

	calculate_each_distance(game);
	sort_sprites(game);
	sprited.i = 0;
	while (sprited.i < game->nb_sprites)
	{
		s_pos[0] = game->sprites[sprited.i].pos[0] + 0.5 - game->pos[0];
		s_pos[1] = game->sprites[sprited.i].pos[1] + 0.5 - game->pos[1];
		inv_det = 1.0 / (game->cam_plane[0] * game->dir[1]
				- game->dir[0] * game->cam_plane[1]);
		sprited.transform[0] = inv_det * (game->dir[1] * s_pos[0]
				- game->dir[0] * s_pos[1]);
		sprited.transform[1] = inv_det * (-game->cam_plane[1] * s_pos[0]
				+ game->cam_plane[0] * s_pos[1]);
		sprited.x = (int)((game->scr_w / 2) *
				(1 + sprited.transform[0] / sprited.transform[1]));
		sprited.size = abs((int)(game->scr_h / sprited.transform[1]));
		draw_sprite(game, sprited);
		sprited.i++;
	}
}
