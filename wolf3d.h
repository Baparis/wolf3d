/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:23:51 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 23:05:59 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include "keymacro.h"
# include <fcntl.h>
# include "mlx.h"
# include "math.h"
# include "colors.h"
# include <sys/types.h>
# include <sys/stat.h>

# define TURN 0.075
# define MS 0.1

typedef struct	s_ima
{
	void		*img_ptr;
	int			bpp;
	int			sl;
	int			en;
	char		*ima;
}				t_ima;

typedef struct	s_map
{
	int			north;
	int			west;
	int			east;
	int			south;
	int			ground;
	int			roof;
}				t_map;

typedef struct	s_play
{
	int			height;
	int			fov;
	int			view;
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
}				t_play;

typedef struct	s_dda
{
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		mapx;
	int		mapy;
	int		hit;
	int		stepx;
	int		stepy;
	int		side;
}				t_dda;

typedef struct	s_write
{
	int		texnum;
	int		texx;
	int		y;
	int		d1;
	int		texy;
	double	distwall;
	double	distplayer;
	double	currentdist;
	double	weight;
	double	currentfloorx;
	double	currentfloory;
	int		ftexx;
	int		ftexy;
}			t_write;

typedef struct	s_texl
{
	unsigned char	tmp[64];
	int				*tex;
	FILE			*img;
	int				x;
	int				y;
	int				tmp2[1];
}				t_texl;

typedef struct	s_para
{
	void		*mlx_ptr;
	void		*win_ptr;
	double		raydirx;
	double		raydiry;
	double		wallx;
	double		floorxwall;
	double		floorywall;
	int			door;
	int			autodoor;
	int			sound;
	int			dox;
	int			doy;
	int			maxx;
	int			maxy;
	char		*title;
	int			**texture;
	int			right;
	int			left;
	int			up;
	int			down;
	int			vent;
	int			exit;
	t_ima		*ima;
	t_map		**map;
	t_play		*p;
}				t_para;

t_para			*ft_mlx_init(char *name);
t_ima			*ft_new_frame(t_para *par);
t_dda			*dda_init(t_para *p, double raydirx, double raydiry);
void			floor_casting(t_para* p, t_dda *d);

void			sideinit(t_dda *d, t_para *p, double raydirx, double raydiry);
void			dda(t_para *par, t_dda *d);
int				calc_height(t_dda *d, t_para *p,\
		double raydiry, double raydirx);

int				ft_key_release(int kaycode, t_para *par);
int				move(t_para *par);

void			scripts(t_para *p);

t_map			**map_loader(char *path, t_para *par);
int			ft_display(t_para *par);
void			horizontal(t_para *par, t_map **map, int i);
void			vertical(t_para *par, t_map **map, int i);
int				ft_real_distance(t_para *par, int angle);
int				ft_run(t_para *par);
void			ft_error(int error);
int				ft_exit(t_para *p);
int				ft_key_rec(int keycode, t_para *p);

#endif
