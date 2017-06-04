/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/03 19:29:55 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 17:33:14 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_put_pixel(t_para *par, int x, int y, int color)
{
	int		i;
	int		chunk;

	i = -1;
	chunk = (x < 640 ? 0 : 1);
	chunk += (y < 400 ? 0 : 2);
	x -= (x < 640 ? 0 : 640);
	y -= (y < 400 ? 0 : 400);
	i = (x * 4) + (y * par->ima->sl);
	par->ima[chunk].ima[i] = color;
	par->ima[chunk].ima[++i] = color >> 8;
	par->ima[chunk].ima[++i] = color >> 16;
}

void	suite(t_para *par, t_dda *d, t_write t, int i)
{
	int		ground;
	int		ceiling;

	floor_casting(par, d);
	t.distwall = d->perpwalldist;
	t.distplayer = 0.0;
	t.y--;
	ground = 3;
	ceiling = 2;
	if (t.texnum == 6 || par->vent == 1)
	{
		par->vent = 1;
		ground = 6;
		ceiling = 6;
	}
	while (t.y < 800)
	{
		t.currentdist = 800.0 / (2.0 * t.y - 800.0);
		t.weight = (t.currentdist - t.distplayer) /\
					(t.distwall - t.distplayer);
		t.currentfloorx = t.weight * par->floorxwall\
						+ (1.0 - t.weight) * par->p->posx;
		t.currentfloory = t.weight * par->floorywall\
						+ (1.0 - t.weight) * par->p->posy;
		t.ftexx = (int)(t.currentfloorx * 64) % 64;
		t.ftexy = (int)(t.currentfloory * 64) % 64;
		ft_put_pixel(par, i, t.y, par->texture[ground]\
				[t.ftexy * 64 + t.ftexx]);
		ft_put_pixel(par, i, 800 - ++t.y, par->texture[ceiling]\
				[t.ftexy * 64 + t.ftexx]);
	}
}

int		ft_write_down(t_para *par, int coord, int i, t_dda *d)
{
	t_write		t;

	t.texnum = abs(par->map[d->mapy][d->mapx].north) - 1;
	t.y = 0;
	if (d->side == 0)
		par->wallx = par->p->posy + d->perpwalldist * par->raydiry;
	else
		par->wallx = par->p->posx + d->perpwalldist * par->raydirx;
	par->wallx -= floor((par->wallx));
	t.texx = (int)(par->wallx * 64.0);
	if (d->side == 0 && par->raydirx > 0)
		t.texx = 64 - t.texx - 1;
	if (d->side == 1 && par->raydiry < 0)
		t.texx = 64 - t.texx - 1;
	while (t.y < 800 && t.y <= coord / 2 + 800 / 2 + 1)
	{
		t.d1 = t.y * 256 - 800 * 128 + coord * 128;
		t.texy = ((t.d1 * 64) / coord) / 258;
		ft_put_pixel(par, i, t.y++, par->texture[t.texnum]\
				[t.texy * 64 + t.texx]);
	}
	suite(par, d, t, i);
	return (1);
}

void	ft_printscreen(t_para *par)
{
	int	i;

	i = -1;
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr,\
			par->ima[0].img_ptr, 0, 0);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr,\
			par->ima[1].img_ptr, 640, 0);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr,\
			par->ima[2].img_ptr, 0, 400);
	mlx_put_image_to_window(par->mlx_ptr, par->win_ptr,\
			par->ima[3].img_ptr, 640, 400);
}

int	ft_display(t_para *par)
{
	int		i;
	t_dda	*d;
	double	camerax;

	i = -1;
	if (!(par->ima))
		par->ima = ft_new_frame(par);
	while (++i < 1280)
	{
		camerax = 2 * i / 1280.0 - 1;
		par->raydirx = par->p->dirx + par->p->planex * camerax;
		par->raydiry = par->p->diry + par->p->planey * camerax;
		d = dda_init(par, par->raydirx, par->raydiry);
		sideinit(d, par, par->raydirx, par->raydiry);
		dda(par, d);
		ft_write_down(par, calc_height(d, par, par->raydiry, par->raydirx)\
				, i, d);
		free(d);
	}
	par->vent = 0;
	ft_printscreen(par);
	scripts(par);
	return (1);
}
