/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:34:11 by habdella          #+#    #+#             */
/*   Updated: 2025/09/25 14:09:43 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCAST_H
# define DCAST_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <sys/time.h>

# include "/home/habdella/include/minilibx-linux/mlx.h"

# define WIDTH		1060
# define HEIGHT		900
# define TILE_SIZE	12
/* --------- colors --------- */
# define BLACK 		0x000000
# define WHITE		0xFFFFFF
# define RED		0xFF0000
# define GREEN		0x00FF00
# define BLUE		0x0000FF
# define DARK_BLUE	0x00008B
# define YELLOW		0xFFFF00
# define CYAN		0x00FFFF
# define MAGENTA	0xFF00FF
# define GRAY		0x808080
# define LIGHT_GRAY	0xD3D3D3
# define DARK_GRAY	0x404040
# define ORANGE		0xFFA500
# define PURPLE		0x800080
# define BROWN		0xA52A2A
/* -------------------------- */
/* ---------- keys ---------- */
# define KEY_ESC	65307
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
/* -------------------------- */
/* ------- directions ------- */
# define	NO		0
# define	EA		1
# define	SO		2
# define	WE		3
# define	FLOOR	4
# define	CEILING	5
/* -------------------------- */
# define WHITESPACES	" \t\n\v\f\r"

# define PI 3.1415927

typedef struct s_colors
{
	char	red;	
	char	blue;	
	char	green;	
}	t_colors;

typedef struct s_player
{
	double	x;
	double	y;
	char	dir;
	float	radius;
	int		turnDirection;
	int		walkDirection;
	float	moveSpeed;
	float	rotationAngle;
	float	rotaionSpeed;
}	t_player;

typedef struct s_map
{
	char	**greed;
	int	map_height;
	int	map_width;
}	t_map;

typedef struct s_display
{
	void		*mlx;
	char		*name;
	void		*window;
	void		*img;
	char		*pixel;
	char		*texture[4];
	int			bpp;
	int			line_len;
	int			endian;
	t_colors	floor;
	t_colors	ceiling;
}	t_display;

typedef struct s_list
{
	char			*line;
	struct s_list 	*next;
}	t_list;

typedef struct s_file
{
	char	*name;
	int		fd;
}	t_file;


typedef struct s_gc
{
	void				*address;
	struct s_gc			*next;
}	t_gc;

typedef struct s_game
{
	char		**split;
	int			split_len;
	t_file		file;
	t_map		map;
	t_player	player;
	t_display	disp;
	t_list		*list;
	t_gc		*collector;
}	t_game;

/* ///////////////// helper functions \\\\\\\\\\\\\\\\\ */

size_t	ft_strlen(const char *s);
void	putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		initial_checks(int argc, char **argv);

int		ft_atoi(const char *nptr);
char	**ft_split(char *str, char *charset, int *nb_words);
int 	check_file_extension(char *str, char *extension);

char	*get_next_line(t_game *game, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
t_game	*save_game(t_game *game);
void	*ft_malloc(size_t size);
char	*ft_strduplen(char *s, int len);
void	clean_exit(char *message);

t_list  *new_node(char *content);
void    add_back(t_list **head, char *content);

bool	is_player(char c);
void	save_cord_player(t_game *game, int x, int y, char direction);

/* ///////////////// parsing functions \\\\\\\\\\\\\\\\\ */

void	parse_map(t_game *game, char *file_name);
void	textures_parse(t_game *game, char *mask, int type);
void	floor_ceiling_parse(t_game *game, char *mask, int type);
void	greed_parse(t_game *game);
void	convert_list_to_array(t_game *game);
void	check_valid_greed(t_game *game);
bool	is_valid_element(char c);
bool	is_empty_line(char *s);

/* ///////////////// events functions \\\\\\\\\\\\\\\\\ */

void    init_events(t_game *game);

/* ///////////////// rendering functions \\\\\\\\\\\\\\\\\ */

void    init_render(t_game *game);
void    minimap_render(t_game *game);
void	my_pixel_put(int x, int y, t_game *game, int color);

/* ///////////////// ray-casting functions \\\\\\\\\\\\\\\\\ */

#endif
