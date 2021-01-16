#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include "get_next_line/get_next_line.h"

# define TRUE 1
# define FALSE 0
# define SUCCESS 0
# define ERROR 1

# define KEY_A 113
# define KEY_S 115
# define KEY_D 100
# define KEY_W 122
# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363

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

typedef struct		s_dda
{
	double			side_dist[2];
	double			delta_dist[2];
	double			wall_dist;
	int				line_height;
	int				map_pos[2];
	int				step[2];
	int				side;
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
	double			*depth_buffer;
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

/**
 * keys
 */
int					key_pressed(int key, t_game *game);
int					key_released(int key, t_game *game);

t_game				*game_init(int ac, char **av);
t_bool				finish_init(t_game *game);
void				init_camera(t_game *game);
t_bool				init_screen(t_game *game);

void				dda(t_game *game, double ray[2], int i);
t_dda				init_dda(t_game *game, double ray[2]);
t_bool				is_hit(t_game *game, t_dda *ddata, double ray[2]);

/**
 * vectors
 */
void		v_scale(double a, double v[2], double u[2]);

/**
 * all parse
 */
void				parse_file(t_game *game);
void				parse_line(t_game *game, char *line, int ret);
void				parse_res(t_game *game, char *pline);
void				parse_text(t_game *game, char *pline, int text);
void				parse_color(t_game *game, char *pline, int which);
void				parse_else(t_game *game, char *pline, int ret);
void				check_before(t_game *game);
void				parse_map1(t_game *game, char *pline);
t_bool				parse_map2(t_game *game);

/**
 * error
 */
void				quit(t_game *game, int ret);
void				parserror(t_game *game, char *msg);

/**
 * utils
 */
int					ft_strcmp(char *s1, char *s2);
int					atonum(char *s);
char				*ft_trim(char *str);
char				*rmempty(char *pline);
int					whereis(char c, char *s);
/**
 * mallfree
 */
void				*ft_calloc(int count, int size);
void				free_game(t_game *game);
#endif
