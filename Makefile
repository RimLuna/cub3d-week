NAME =		cub3D

SRCS=		stupid_bmp.c \
			keys.c \
			draw.c \
			init_necessary.c \
			init_map.c \
			parse_things.c \
			parse_file.c \
			utils.c mallfree.c \
			errors.c \
			init.c \
			main.c \
			get_next_line/get_next_line.c \
			get_next_line/get_next_line_utils.c

FLAGS =		-Wall -Wextra

MLX_INC =		/usr/X11/include
MLX_LIB =		/usr/X11/lib
MLX_FLAGS =	-lX11 -lXext
MLX_FLAGS += -L/usr/X11/lib /usr/X11/lib/libmlx.a -lXext -lX11 -lbsd

# mac
MLXDIR = ./mlx
MLX_FLAGS = -framework OpenGL -framework AppKit
MLX_INC = $(MLXDIR)
MLX_LIB = $(addprefix $(MLXDIR)/,libmlx.a)

all:		$(NAME) $(MLX_LIB)

$(NAME):	$(SRCS) get_next_line/get_next_line.h cub3d.h $(MLX_LIB)
			gcc $(FLAGS) -I $(MLX_INC) -g -L $(MLX_LIB) $(SRCS) -lm -o $(NAME) $(MLX_FLAGS)

$(MLX_LIB):
			@make -C $(MLXDIR)

clean:
			rm -rf $(SRCS:.c=.o)
			make -C $(MLXDIR) clean

fclean:		clean
			rm -f $(NAME)
			make -C $(MLXDIR) fclean

re:			fclean all 
