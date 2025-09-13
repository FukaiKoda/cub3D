/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Dcast.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habdella <habdella@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:34:11 by habdella          #+#    #+#             */
/*   Updated: 2025/09/13 15:44:24 by habdella         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DCAST_H
# define DCAST_H

# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>

# include "/home/habdella/include/minilibx-linux/mlx.h"

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

# define WIDTH	800
# define HEIGHT	800

typedef struct s_player
{
	double	x;
	double	y;
	double	dir;
}	t_player;

typedef struct s_display
{
	void	*mlx;
	char	*name;
	void	*window;
	void	*img;
	char	*pixel;
	int		bpp;
	int		line_len;
	int		endian;
}	t_display;

typedef struct s_gc
{
	void				*address;
	struct s_gc			*next;
}	t_gc;

typedef struct s_game
{
	t_player	player;
	t_display	disp;
	t_gc		*collector;
}	t_game;

/* ///////////////// parsing functions \\\\\\\\\\\\\\\\\ */



/* ///////////////// helper functions \\\\\\\\\\\\\\\\\ */

void	*ft_malloc(t_game *game, size_t size);
void	clean_exit(t_game *game);

/* ///////////////// ray-casting functions \\\\\\\\\\\\\\\\\ */



/* ///////////////// rendering functions \\\\\\\\\\\\\\\\\ */



#endif
