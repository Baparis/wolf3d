/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 12:13:54 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 16:17:23 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	sideinit(t_dda *d, t_para *p, double raydirx, double raydiry)
{
	if (raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (p->p->posx - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - p->p->posx) * d->deltadistx;
	}
	if (raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (p->p->posy - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - p->p->posy) * d->deltadisty;
	}
}

void	dda(t_para *par, t_dda *d)
{
	while (d->hit == 0)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (par->map[d->mapy][d->mapx].north > 0)
			d->hit = 1;
		if (par->map[d->mapy][d->mapx].north != -5 &&\
				par->map[d->mapy][d->mapx].north < 0)
			d->hit = 1;
	}
}

int		calc_height(t_dda *d, t_para *p, double raydiry, double raydirx)
{
	if (d->side == 0)
		d->perpwalldist = (d->mapx - p->p->posx + (1 - d->stepx) / 2) / raydirx;
	else
		d->perpwalldist = (d->mapy - p->p->posy + (1 - d->stepy) / 2) / raydiry;
	return ((int)(800 / d->perpwalldist));
}

void	floor_casting(t_para *p, t_dda *d)
{
	if (d->side == 0 && p->raydirx > 0)
	{
		p->floorxwall = d->mapx;
		p->floorywall = d->mapy + p->wallx;
	}
	else if (d->side == 0 && p->raydirx < 0)
	{
		p->floorxwall = d->mapx + 1.0;
		p->floorywall = d->mapy + p->wallx;
	}
	else if (d->side == 1 && p->raydiry > 0)
	{
		p->floorxwall = d->mapx + p->wallx;
		p->floorywall = d->mapy;
	}
	else
	{
		p->floorxwall = d->mapx + p->wallx;
		p->floorywall = d->mapy + 1.0;
	}
}
