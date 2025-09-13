CC = cc

CFLAGS = -Wall -Wextra -Werror

HA_MLX_FLAGS = -L/home/habdella/include/minilibx-linux -lmlx -lXext -lX11 -lm
#OA_MLX_FLAGS = -L/home/oayyoub/include/minilibx-linux -lmlx -lXext -lX11 -lm

SRC = src/main.c \
      src/events/*.c \
      src/helpers/*.c \
      src/parsing/*.c \
      src/raycast/*.c \
      src/render/*.c

OBJ = ${SRC:%.c=%.o}

INC = Dcast.h

RM = rm -f

NAME = cub3D

all: ${NAME}

${NAME}: ${OBJ}
	${CC} ${CFLAGS} ${HA_MLX_FLAGS} ${OBJ} -o $@

%.o: ${INC} %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJ}

fclean: clean
	${RM} ${NAME}

re: fclean all

bonus: all


.PHONY: all clean fclean re bonus

.SECONDARY: ${OBJ}