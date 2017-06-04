/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scripts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/29 16:57:16 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 17:43:30 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	scripts(t_para *p)
{
	if (p->map[(int)(p->p->posy + (p->p->diry * MS * 12))][(int)(p->p->posx\
				+ (p->p->dirx * MS * 12))].north == 2)
	{
		mlx_string_put(p->mlx_ptr, p->win_ptr, 600, 500, 0xFFFFFF,\
				"Press E to open");
		p->door = 1;
	}
	if (p->map[(int)(p->p->posy + (p->p->diry * MS * 12))][(int)(p->p->posx\
				+ (p->p->dirx * MS * 12))].north == 5 && p->autodoor == 0)
	{
			p->autodoor = 1;
			p->dox = p->p->posx + p->p->dirx * MS * 12;
			p->doy = p->p->posy + p->p->diry * MS * 12;
	}
	if (p->map[(int)(p->p->posy + (p->p->diry * MS * 12))][(int)(p->p->posx\
				+ (p->p->dirx * MS * 12))].north == 9 ||\
			p->map[(int)(p->p->posy + (p->p->diry * MS * 12))][(int)(p->p->posx\
				+ (p->p->dirx * MS * 12))].north == 10)
	{
		mlx_string_put(p->mlx_ptr, p->win_ptr, 600, 500, 0xFFFFFF,\
				"Press E to get away");
		p->exit = 1;
	}
}
