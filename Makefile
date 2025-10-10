CC = cc

CFLAGS = -Wall -Wextra -Werror -I Dcast.h
MLX_DIR = /home/oayyoub/include/minilibx-linux

CFLAGS = -Wall -Wextra -Werror -I include -I $(MLX_DIR)
LDFLAGS = -L$(MLX_DIR)
LDLIBS  = -lmlx_Linux -lXext -lX11 -lm -lz

SRC =	src/main.c \
		src/helpers/string_manip.c src/helpers/garbage_collector.c src/helpers/input_checks.c \
		src/helpers/get_next_line.c src/helpers/atoi_split.c src/helpers/list_helpers.c \
		src/helpers/greed_helpers.c src/helpers/init_textures.c src/helpers/fps.c \
		src/parsing/file_parse.c src/parsing/types_parse.c src/parsing/greed_parse.c \
		src/render/init_render.c src/render/minimap.c src/render/rendering.c src/render/draw_utils.c \
		src/player/player_movement.c \
		src/events/events.c \
		src/raycast/raycast.c src/raycast/raycast_utils.c src/raycast/horizontal_rays.c src/raycast/vertical_rays.c \

OBJ = ${SRC:%.c=%.o}

RM = rm -f

NAME = cub3D

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} -g ${OBJ} ${LDFLAGS} ${LDLIBS} -o $@

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: all


.PHONY: all clean fclean re bonus

.SECONDARY: ${OBJ}