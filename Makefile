CC = cc

CFLAGS = -Wall -Wextra -Werror -I Dcast.h

HA_MLX_FLAGS = -L/home/habdella/include/minilibx-linux -lmlx -lXext -lX11 -lm
#OA_MLX_FLAGS = -L/home/oayyoub/include/minilibx-linux -lmlx -lXext -lX11 -lm

#src/raycast/*.c 
#src/render/*.c
#src/events/*.c

SRC = src/main.c \
      src/helpers/string_manip.c src/helpers/garbage_collector.c src/helpers/input_checks.c \
      src/helpers/get_next_line.c src/helpers/atoi_split.c src/helpers/list_helpers.c \
      src/helpers/greed_helpers.c \
      src/parsing/file_parse.c src/parsing/types_parse.c src/parsing/greed_parse.c \

OBJ = ${SRC:%.c=%.o}

RM = rm -f

NAME = cub3D

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${HA_MLX_FLAGS} -g ${OBJ} -o $@

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