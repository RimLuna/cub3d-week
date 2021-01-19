/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:35:44 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/19 16:35:44 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				check_before(t_game *game)
{
	if (!game->scr_w)
		parserror(game, "where s the resolution??\n");
	else if (!game->textures[N].filename)
		parserror(game, "where s the north texture??\n");
	else if (!game->textures[W].filename)
		parserror(game, "where s the west texture??\n");
	else if (!game->textures[E].filename)
		parserror(game, "where s the east texture??\n");
	else if (!game->textures[S].filename)
		parserror(game, "where s the south texture??\n");
	else if (!game->sprite_txt.filename)
		parserror(game, "where s the sprite texture??\n");
	else if (!(game->color_set[0] & game->color_set[1]))
		parserror(game, "where r the colors??\n");
}

void				parse_line(t_game *game, char *line, int ret)
{
	char		*pline;

	pline = line;
	while (*pline && *pline <= ' ')
		pline++;
	if (*pline == 'R')
		parse_res(game, pline + 1);
	else if (*pline == 'N' && *(pline + 1) == 'O')
		parse_text(game, pline + 2, N);
	else if (*pline == 'S' && *(pline + 1) == 'O')
		parse_text(game, pline + 2, S);
	else if (*pline == 'W' && *(pline + 1) == 'E')
		parse_text(game, pline + 2, W);
	else if (*pline == 'E' && *(pline + 1) == 'A')
		parse_text(game, pline + 2, E);
	else if (*pline == 'F' || *pline == 'C')
		parse_color(game, pline + 1, *pline);
	else if (*pline == 'S')
		parse_text(game, pline + 1, 4);
	else
		parse_else(game, line, ret);
}

void				parse_file(t_game *game)
{
	char		*line;
	int			ret;
	int			i;

	i = 1;
	while ((ret = get_next_line(game->fd, &line)) >= 0)
	{
		parse_line(game, line, ret);
		free(line);
		i++;
		if (ret == 0)
			break ;
	}
	if (ret == -1)
		parserror(game, "weird file!\n");
	close(game->fd);
}
