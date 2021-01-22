/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:47 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 16:21:34 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		parse_res(t_game *game, char *pline)
{
	if (game->scr_w)
		p_err(game, "res is already there!\n");
	while (*pline <= ' ')
		pline++;
	game->scr_w = a2n(pline);
	while (*pline >= '0' && *pline <= '9')
		pline++;
	while (*pline <= ' ')
		pline++;
	game->scr_h = a2n(pline);
	while (*pline >= '0' && *pline <= '9')
		pline++;
	if (game->scr_w < 0 || game->scr_h < 0)
		p_err(game, "OVERFLOW!\n");
	pline = rmempty(pline);
	if (game->scr_h == 0 || game->scr_w == 0 || ft_strlen(pline) > 0)
		p_err(game, "res??\n");
	game->scr_w = game->scr_w > 2560 ? 2560 : game->scr_w;
	game->scr_w = game->scr_w < 800 ? 800 : game->scr_w;
	game->scr_h = game->scr_h > 1440 ? 1440 : game->scr_h;
	game->scr_h = game->scr_h < 480 ? 480 : game->scr_h;
	free(pline);
}

void		parse_text(t_game *game, char *pline, int text)
{
	t_img		*texture;

	if (text == 4 && game->sprite_txt.filename)
		p_err(game, "dont write the sprite texture twice!!\n");
	else if (text < 4 && game->textures[text].filename)
		p_err(game, "wall texture is here already!!\n");
	else
	{
		texture = (text < 4) ? &(game->textures[text]) : &(game->sprite_txt);
		while (*pline <= ' ')
			pline++;
		texture->filename = ft_strdup(ft_trim(pline));
		if (open(texture->filename, O_RDONLY) < 0)
			p_err(game, "write a correct texture file!!\n");
	}
}

t_bool		c(int color)
{
	if (color >= 0 && color <= 255)
		return (TRUE);
	return (FALSE);
}

void		parse_color(t_game *game, char *pl, int which)
{
	int		color;
	int		i;

	if (which == 'F' && game->color_floor)
		p_err(game, "another floor color??\n");
	else if (which == 'C' && game->color_ceil)
		p_err(game, "another ceiling color??\n");
	i = 0;
	color = 0;
	which == 'F' ? game->color_set[0]++ : game->color_set[1]++;
	while (i++ < 3)
	{
		while (*pl <= ' ')
			pl++;
		if (*pl > '9' || *pl < '0')
			p_err(game, "thats not a color!\n");
		c(a2n(pl)) ? color = (color << 8) + a2n(pl) : p_err(game, "color?!\n");
		while (*pl >= '0' && *pl <= '9')
			pl++;
		(*pl == ',' || i == 3) ? pl++ : p_err(game, "not a color!\n");
	}
	if (which == 'F')
		game->color_floor = color;
	else
		game->color_ceil = color;
}

void		parse_else(t_game *game, char *pline, int ret)
{
	char	*rmemptyp;

	rmemptyp = rmempty(pline);
	if (ft_strlen(rmemptyp) > 0 && whereis(*rmemptyp, "012NSWE") >= 0)
		parse_map1(game, pline);
	else if (ft_strlen(rmemptyp) > 0 && whereis(*rmemptyp, "012NSWE") < 0)
		p_err(game, "huh?\n");
	else if (game->raw_map && ret > 0)
		p_err(game, "empty line in map!!\n");
	free(rmemptyp);
}
