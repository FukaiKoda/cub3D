CC = cc

CFLAGS = -Wall -Wextra -Werror -I include/

HA_MLX_FLAGS = -L/home/habdella/include/minilibx-linux -lmlx -lXext -lX11 -lm
#OA_MLX_FLAGS = -L/home/oayyoub/include/minilibx-linux -lmlx -lXext -lX11 -lm

#src/raycast/*.c 

SRC = src/main.c \
      src/helpers/string_manip.c src/helpers/garbage_collector.c src/helpers/input_checks.c \
      src/helpers/get_next_line.c src/helpers/atoi_split.c src/helpers/list_helpers.c \
      src/helpers/greed_helpers.c \
      src/parsing/file_parse.c src/parsing/types_parse.c src/parsing/greed_parse.c \
	  src/render/init_render.c src/render/minimap_render.c \
	  src/events/events.c

OBJ = ${SRC:%.c=%.o}

RM = rm -f

NAME = cub3D

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} ${HA_MLX_FLAGS} -g -o $@

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