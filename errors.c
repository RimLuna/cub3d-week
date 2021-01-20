/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 16:36:08 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/19 16:36:09 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				die(t_game *game, int ret)
{
	free_game(game);
	exit(ret);
}

void				parserror(t_game *game, char *msg)
{
	if (game->error)
		return ;
	write(1, "Error:\n", 7);
	write(1, msg, ft_strlen(msg));
	game->error = 1;
}
