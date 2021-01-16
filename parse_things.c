#include "cub3d.h"

void		parse_res(t_game *game, char *pline)
{
	if (game->scr_w)
		parserror(game, "dude res is already there!\n");
	while (*pline <= ' ')
		pline++;
	game->scr_w = atonum(pline);
	while (*pline >= '0' && *pline <= '9')
		pline++;
	while (*pline <= ' ')
		pline++;
	game->scr_h = atonum(pline);
	while (*pline >= '0' && *pline <= '9')
		pline++;
	pline = rmempty(pline);
	if (game->scr_h == 0 || game->scr_w == 0 || ft_strlen(pline) > 0)
		parserror(game, "fcking res\n");
	game->scr_w = (game->scr_w > 1098) ? 1098 : (game->scr_w < 800 ? 800 : game->scr_w);
	game->scr_h = (game->scr_h > 1000) ? 1000 : (game->scr_h < 480 ? 480 : game->scr_h);
	free(pline);
}

void		parse_text(t_game *game, char *pline, int text)
{
	t_img		*texture;

	if (text == 4 && game->sprite_txt.filename)
		parserror(game, "dont write the sprite texture twice, tf!!\n");
	else if (text < 4 && game->textures[text].filename)
		parserror(game, "wall texture is here already!!\n");
	else
	{
		texture = (text < 4) ? &(game->textures[text]) : &(game->sprite_txt);
		while (*pline <= ' ')
			pline++;
		texture->filename = ft_strdup(ft_trim(pline));
		if (open(texture->filename, O_RDONLY) < 0)
			parserror(game, "write a correct texture file!!\n");
	}
}

void		parse_color(t_game *game, char *pline, int which)
{
	int		color;
	int		i;

	if (which == 'F' && game->color_floor)
		parserror(game, "another floor color??\n");
	else if (which == 'C' && game->color_ceil)
		parserror(game, "another ceiling color??\n");
	i = 0;
	color = 0;
	which == 'F' ? game->color_set[0]++ : game->color_set[1]++;
	while (i++ < 3)
	{
		while (*pline <= ' ')
			pline++;
		if (*pline > '9' || *pline < '0')
			parserror(game, "thats not a color!\n");
		color = (color << 8) + atonum(pline);
		while (*pline >= '0' && *pline <= '9')
			pline++;
		if (*pline == ',' || i == 3)
			pline++;
		else
			parserror(game, "thats not a color!\n");
	}
	if (which == 'F')
		game->color_floor = color;
	else
		game->color_ceil = color;
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

void		parse_else(t_game *game, char *pline, int ret)
{
	char	*rmemptyp;

	rmemptyp = rmempty(pline);
	if (ft_strlen(rmemptyp) > 0 && whereis(*rmemptyp, "012NSWE") >= 0)
		parse_map1(game, pline);
	else if (ft_strlen(rmemptyp) > 0 && whereis(*rmemptyp, "012NSWE") < 0)
		parserror(game, "huh?\n");
	else if (game->raw_map && ret > 0)
		parserror(game, "empty line in map!!\n");
	free(rmemptyp);
}
