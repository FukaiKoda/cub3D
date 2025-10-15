/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:34:11 by habdella          #+#    #+#             */
/*   Updated: 2025/10/15 20:34:13 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCAST_H
# define DCAST_H

/* ******************************* INCLUDES ******************************* */
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

# include "/home/hatim/include/minilibx-linux/mlx.h"

/* ******************************* DEFINES ******************************* */
# define WIDTH				1300
# define HEIGHT				700
# define TILE_SIZE			64
# define FOV_ANGLE			1.047197551
# define WALL_STRIP_WIDTH	1
# define BUFFER_SIZE		1337
# define WHITESPACES		" \t\n\v\f\r"
# define MOUSE_SENSITIVITY	0.0025

/* Colors */
# define BLACK				0x000000
# define WHITE				0xFFFFFF
# define RED				0xFF0000
# define GREEN				0x00FF00
# define BLUE				0x0000FF
# define DARK_BLUE			0x00008B
# define YELLOW				0xFFFF00
# define CYAN				0x00FFFF
# define MAGENTA			0xFF00FF
# define GRAY				0x808080
# define LIGHT_GRAY			0xD3D3D3
# define DARK_GRAY			0x404040
# define ORANGE				0xFFA500
# define PURPLE				0x800080
# define BROWN				0xA52A2A

/* keycode */
# define KEY_W        119
# define KEY_A        97
# define KEY_S        115
# define KEY_D        100

# define KEY_H		  104
# define KEY_R		  114

# define KEY_O		  111

# define KEY_LEFT     65361
# define KEY_RIGHT    65363
# define KEY_ESC      65307
# define KEY_TAB      65289

/* ******************************* ENUMS ********************************* */
enum e_texture_type
{
	NO,
	EA,
	SO,
	WE,
	FLOOR,
	CEILING
};
# define DOOR 4 
/* ******************************* TYPES ********************************* */
typedef struct s_coord
{
	float	x;
	float	y;
}	t_coord;

typedef struct s_player
{
	t_coord	pos;
	float	radius;
	char	turn_direction;
	char	walk_direction;
	char	strafe_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	bool	is_exist;
}	t_player;

typedef struct s_ray
{
	float	ray_angle;
	t_coord	wall_hit;
	float	distance;
	bool	vertical_door;
	bool	horizontal_door;
	bool	is_ray_facing_down;
	bool	is_ray_facing_up;
	bool	is_ray_facing_right;
	bool	is_ray_facing_left;
	int		wall_side;
	float	wall_x;
}	t_ray;

typedef struct s_hit
{
	t_coord	pos;
	float	distance;
	bool	found;
}	t_hit;

typedef struct s_step
{
	t_coord	pos;
	t_coord	step;
}	t_step;

typedef struct s_map
{
	char	**grid;
	int		map_height;
	int		map_width;
}	t_map;

typedef struct s_texture
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
	bool	is_animated;
}	t_texture;

typedef struct s_texture_anim
{
	t_texture	frames[6];
	int			num_frames;
	int			current_frame;
	float		frame_time;
	float		elapsed_time;
}	t_tex_anim;

typedef struct s_door
{
	int			x;
	int			y;
	bool		is_open;
}	t_door;

typedef struct s_display
{
	void		*mlx;
	char		*name;
	void		*window;
	void		*img;
	char		*pixel;
	char		*texture[4];
	t_texture	tex[5];
	t_tex_anim	tex_anim;
	t_door		*doors;
	int			num_doors;
	int			bpp;
	int			line_len;
	int			endian;
	int			floor;
	int			ceiling;
}	t_display;

typedef struct s_list
{
	char			*line;
	struct s_list	*next;
}	t_list;

typedef struct s_file
{
	char	*name;
	int		fd;
}	t_file;

typedef struct s_gc
{
	void			*address;
	struct s_gc		*next;
}	t_gc;

typedef struct s_wall
{
	float	height;
	float	top;
	float	bottom;
	int		start;
	int		end;
	int		tex_x;
	int		screen_x;
}	t_wall;

typedef struct s_tex
{
	float	step;
	float	pos;
	float	base;
	int		y;
	int		column;
	int		tex_y;
	int		color;
}	t_tex;

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
	float		angle_step;
	int			num_rays;
	int			fps;
	bool		display_minimap;
	bool		mouse_pause;
	float		half_fov;
	float		half_width;
	float		half_height;
	float		proj_plane_dist;
}	t_game;

/* ******************************* HELPERS ******************************* */
size_t	ft_strlen(const char *s);
void	putstr_fd(char *s, int fd);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strchr(const char *s, int c);
int		initial_checks(int argc, char **argv);
float	normalize_angle(float angle);
void	init_rendering(t_game *game);

int		ft_atoi(const char *nptr);
char	**ft_split(char *str, char *charset, int *nb_words);
int		check_file_extension(char *str, char *extension);

char	*get_next_line(t_game *game, int fd);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s);
t_game	*save_game(t_game *game);
void	*ft_malloc(size_t size);
char	*ft_strduplen(char *s, int len);
void	clean_exit(char *message);
int		exit_game(void *arg);

t_list	*new_node(char *content);
void	add_back(t_list **head, char *content);

void	count_doors(t_game *game, char *line);
void	save_doors_coord(t_game *game);

void	init_animated_textures(t_game *game, char *paths[]);
void	load_animated_texture(t_game *game, int index, char *path);
void	clean_animated_textures(t_game *game);
void	load_door_texture(t_game *game);
bool	is_closed_door(t_game *game, bool *horz_vert, float x, float y);

/* ******************************* PARSING ******************************* */
void	parse_map(t_game *game, char *file_name);
void	textures_parse(t_game *game, char *mask, int type);
void	floor_ceiling_parse(t_game *game, char *mask, int type);
void	grid_parse(t_game *game);
void	convert_list_to_array(t_game *game);
void	check_valid_grid(t_game *game);
bool	is_valid_element(char c);
bool	is_empty_line(char *s);

/* ******************************* RAY CASTING *************************** */
void	init_rays(t_game *game);
float	distance_between_points(float x1, float y1, float x2, float y2);
int		is_inside_map(t_game *game, float x, float y);
bool	is_wall(t_game *game, float x, float y);
t_hit	find_horizontal(t_game *game, t_ray *ray, t_coord player);
t_hit	find_vertical(t_game *game, t_ray *ray, t_coord player);
t_ray	cast_single_ray(t_game *game, float angle, t_coord player);

/* ******************************* RENDERING ***************************** */
void	render_3d(t_game *game);
void	init_events(t_game *game);
void	display_minimap(t_game *game);
void	update_animation(t_game *game);

void	mouse_interaction(int keycode, t_game *game);
void	door_interaction(t_game *game);

/* ******************************* DRAW UTILS **************************** */
void	my_pixel_put(int x, int y, t_game *game, int color);
void	rectangle(t_game *game, t_coord pos, t_coord size, int color);

/* ******************************* PLAYER ******************************* */
bool	is_player(char c);
void	save_cord_player(t_game *game, int i, int j, char direction);
void	init_player(t_game *game);
void	update_player(t_game *game);
void	update_player_strafe(t_game *game);
void	strafe_direction(int keycode, t_game *game);
void	walk_turn_direction(int keycode, t_game *game);
bool	is_valid_position(t_game *game, int x, int y);

/* ******************************* TEXTURES ****************************** */
void	init_textures(t_game *game);
void	cleanup_textures(t_game *game);
int		get_texture_color(t_texture *texture, int x, int y);

/* ***************************** FPS AND TIME ***************************** */
double	get_time_ms(void);
void	fps_counter(t_game *game);
void	display_fps(t_game *game);

#endif