/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbougssi <rbougssi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 12:18:25 by rbougssi          #+#    #+#             */
/*   Updated: 2021/01/24 18:41:48 by rbougssi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

# define SPEED 15
# define TURN 0.05

# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_W 13

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126

# define KEY_ESC 53

typedef int			t_bool;

typedef enum		e_side
{
	N,
	W,
	S,
	E
}					t_side;

typedef struct		s_mlx
{
	void			*ptr;
	void			*win;
}					t_mlx;

typedef struct		s_text
{
	double			wall_dist;
	double			wall_x;
	int				line_height;
	t_side			side;
}					t_text;

typedef struct		s_sprited
{
	double	transform[2];
	int		x;
	int		size;
	int		i;
}					t_sprited;

typedef struct		s_dda
{
	double			side_dist[2];
	double			delta_dist[2];
	double			wall_dist;
	int				line_height;
	int				map_pos[2];
	int				step[2];
}					t_dda;

typedef struct		s_ctrls
{
	t_bool			w;
	t_bool			a;
	t_bool			s;
	t_bool			d;
	t_bool			left;
	t_bool			right;
}					t_ctrls;

typedef struct		s_img
{
	char			*filename;
	void			*ptr;
	int				width;
	int				height;
	char			*data;
	int				bpp;
	int				size_line;
	t_bool			endian;
}					t_img;

typedef struct		s_sprite
{
	int		pos[2];
	double	distance;
	t_img	texture;
}					t_sprite;

typedef struct		s_game
{
	int				fd;
	int				scr_w;
	int				scr_h;
	int				map_w;
	int				map_h;
	int				nb_pixels;
	double			*z_buffer;
	char			*raw_map;
	char			**char_map;
	int				**map;
	int				color_floor;
	int				color_ceil;
	int				nb_sprites;
	double			pos[2];
	double			dir[2];
	double			cam_plane[2];
	int				fd_save;
	t_mlx			mlx;
	t_bool			color_set[2];
	t_bool			error;
	t_img			textures[4];
	t_sprite		*sprites;
	t_img			sprite_txt;
	t_img			screen;
	t_ctrls			ctrls;
	t_bool			save;
	t_side			cam_dir;
}					t_game;

void				get_h(t_game *game, int i);
void				init_map(t_game *game);
void				check_map(t_game *game);
void				ugh_bmp(t_game *game);
void				bmp_header(t_game *game);
void				reverse_for_bmp(t_game *game);
int					key_pressed(int key, t_game *game);
int					key_released(int key, t_game *game);
t_game				*game_init(int ac, char **av);
t_bool				finish_init(t_game *game);
void				init_camera(t_game *game);
t_bool				init_screen(t_game *game);
void				draw(t_game *game);
void				wallz(t_game *game);
void				spr1tes(t_game *game);
int					texture_to_color(t_img texture_img,
		double wall_x, double x);
void				draw_line(int x, t_game *game, t_text the_texture);
void				put_it(t_img screen, int i, int j, int color);
void				dda(t_game *game, double ray[2], int i);
t_dda				init_dda(t_game *game, double ray[2]);
t_bool				is_hit(t_game *game, t_dda *ddata,
		t_text *texture, double ray[2]);
void				v_scale(double a, double v[2], double u[2]);
void				parse_file(t_game *game);
void				parse_line(t_game *game, char *line, int ret);
void				parse_res(t_game *game, char *pline);
void				parse_text(t_game *game, char *pline, int text);
void				parse_color(t_game *game, char *pl, int which);
void				parse_else(t_game *game, char *pline, int ret);
void				check_before(t_game *game);
void				parse_map1(t_game *game, char *pline);
t_bool				parse_map2(t_game *game);
void				die(t_game *game, int ret);
void				p_err(t_game *game, char *msg);
int					ft_strcmp(char *s1, char *s2);
int					a2n(char *s);
char				*ft_trim(char *str);
char				*rmempty(char *pline);
int					whereis(char c, char *s);
void				*ft_calloc(int count, int size);
void				free_game(t_game *game);
#endif
