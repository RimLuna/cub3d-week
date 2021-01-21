/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:13:03 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/21 12:17:04 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_bool		parse_map2(t_game *game)
{
	int			i;
	char		*p;

	i = 0;
	game->map_h = 0;
	while (game->raw_map[i])
	{
		if (game->raw_map[i] == '\n')
			game->map_h++;
		i++;
	}
	if (!(game->char_map = ft_calloc(game->map_h, sizeof(char *))))
		return (FALSE);
	p = game->raw_map;
	i = 0;
	game->map_w = 0;
	while (i < game->map_h)
		get_h(game, i++);
	free(p);
	init_map(game);
	check_map(game);
	if (game->error)
		die(game, ERROR);
	return (TRUE);
}

void		parse_map1(t_game *game, char *pline)
{
	char	*tmp;

	check_before(game);
	pline = ft_trim(pline);
	if (!game->raw_map)
		game->raw_map = ft_strdup(pline);
	else
	{
		tmp = game->raw_map;
		game->raw_map = ft_strjoin(game->raw_map, pline);
		free(tmp);
	}
	tmp = game->raw_map;
	game->raw_map = ft_strjoin(game->raw_map, "\n");
	free(tmp);
}
