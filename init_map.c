/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:36:17 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/19 16:36:18 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		get_h(t_game *game, int i)
{
	int		j;

	j = 0;
	while (game->raw_map[j] && game->raw_map[j] != '\n')
		j++;
	game->char_map[i] = ft_substr(game->raw_map, 0, j);
	game->raw_map += j + 1;
	j = 0;
	while (game->char_map[i][j])
	{
		if (whereis(game->char_map[i][j], " \t012NSWE") < 0)
			parserror(game, "invalid chars in map\n");
		j++;
	}
	if (ft_strlen(game->char_map[i]) > game->map_w)
		game->map_w = ft_strlen(game->char_map[i]);
}

void		fill_int_map(t_game *game, t_bool *is, int i, int j)
{
	if (j > ft_strlen(game->char_map[i]) || game->char_map[i][j] <= ' ')
		game->map[i][j] = -1;
	else if (whereis(game->char_map[i][j], "012") >= 0)
		game->map[i][j] = game->char_map[i][j] - '0';
	else if (whereis(game->char_map[i][j], "NSWE") >= 0)
	{
		if (*is)
			parserror(game, "player already somewhere else\n");
		else
		{
			game->cam_dir = whereis(game->char_map[i][j], "NWSE");
			game->map[i][j] = 0;
			game->pos[0] = i;
			game->pos[1] = j;
			*is = TRUE;
		}
	}
	if (game->map[i][j] == 2)
		game->nb_sprites++;
}

void		init_map(t_game *game)
{
	t_bool		is_player_pos;
	int			i;
	int			j;

	is_player_pos = FALSE;
	game->map = ft_calloc(game->map_h, sizeof(int *));
	game->nb_sprites = 0;
	i = 0;
	while (i < game->map_h)
	{
		game->map[i] = ft_calloc(game->map_w, sizeof(int));
		j = 0;
		while (j < game->map_w)
			fill_int_map(game, &is_player_pos, i, j++);
		free(game->char_map[i]);
		i++;
	}
	if (!is_player_pos)
		parserror(game, "where the f is the player\n");
	free(game->char_map);
}

t_bool		check_map_ij(t_game *game, int i, int j)
{
	return (!((i == 0 || j == 0 || i == game->map_h - 1 || j == game->map_w - 1
		|| game->map[i - 1][j] == -1 || game->map[i + 1][j] == -1
		|| game->map[i][j - 1] == -1 || game->map[i][j + 1] == -1)
		&& game->map[i][j] != 1 && game->map[i][j] != -1));
}

void		check_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map_h)
	{
		j = 0;
		while (j < game->map_w)
		{
			if (!check_map_ij(game, i, j))
				parserror(game, "invalid fucking map\n");
			j++;
		}
		i++;
	}
}

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
		quit(game, ERROR);
	return (TRUE);
}
