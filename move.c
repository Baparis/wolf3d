/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/26 13:14:27 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 18:20:51 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	next(int keycode, t_para *p)
{
	if (p->autodoor == 1)
	{
		if (p->sound == 0)
		{
			system("afplay Sounds/autopen.mp3&");
			p->sound = 1;
		}
		if (abs((int)p->p->posx - p->dox) > 1 || abs((int)p->p->posy\
					- p->doy) > 1)
		{
			p->map[p->doy][p->dox].north = 5;
			system("afplay Sounds/autopen.mp3&");
			p->sound = 0;
			p->autodoor = 0;
		}
		else
			p->map[p->doy][p->dox].north = -5;
		ft_display(p);
	}
}

int		ft_key_rec(int keycode, t_para *p)
{
	if (keycode == ESC)
		ft_exit(p);
	if (keycode == UP)
		p->up = 1;
	if (keycode == RIGHT)
		p->right = 1;
	if (keycode == LEFT)
		p->left = 1;
	if (keycode == DOWN)
		p->down = 1;
	if (keycode == E && p->door == 1)
	{
		p->door = 0;
		if (p->map[(int)(p->p->posy + (p->p->diry * MS * 12))]\
				[(int)(p->p->posx + (p->p->dirx * MS * 12))].north == 2)
		{
			p->map[(int)(p->p->posy + (p->p->diry * MS * 12))]\
					[(int)(p->p->posx + (p->p->dirx * MS * 12))].north = 0;
			system("afplay Sounds/door.mp3&");
			ft_display(p);
		}
	}
	if (keycode == E && (p->map[(int)(p->p->posy + (p->p->diry * MS * 12))]\
				[(int)(p->p->posx + (p->p->dirx * MS * 12))].north == 9 ||\
				p->map[(int)(p->p->posy + (p->p->diry * MS * 12))]\
				[(int)(p->p->posx + (p->p->dirx * MS * 12))].north == 10))
	{
		system("killall afplay");
		system("afplay Sounds/congratulation.mp3&");
		sleep(5);
		ft_exit(p);
	}
	next(keycode, p);
	return (0);
}

int		ft_key_release(int keycode, t_para *p)
{
	if (keycode == RIGHT)
		p->right = 0;
	if (keycode == LEFT)
		p->left = 0;
	if (keycode == UP)
		p->up = 0;
	if (keycode == DOWN)
		p->down = 0;
	return (0);
}

void	move_2(t_para *p)
{
	double old;

	if (p->right == 1)
	{
		old = p->p->dirx;
		p->p->dirx = p->p->dirx * cos(-TURN) - p->p->diry * sin(-TURN);
		p->p->diry = old * sin(-TURN) + p->p->diry * cos(-TURN);
		old = p->p->planex;
		p->p->planex = p->p->planex * cos(-TURN) - p->p->planey * sin(-TURN);
		p->p->planey = old * sin(-TURN) + p->p->planey * cos(-TURN);
	}
	if (p->left == 1)
	{
		old = p->p->dirx;
		p->p->dirx = p->p->dirx * cos(TURN) - p->p->diry * sin(TURN);
		p->p->diry = old * sin(TURN) + p->p->diry * cos(TURN);
		old = p->p->planex;
		p->p->planex = p->p->planex * cos(TURN) - p->p->planey * sin(TURN);
		p->p->planey = old * sin(TURN) + p->p->planey * cos(TURN);
	}
}

int		move(t_para *p)
{
	if (p->up == 1)
	{
		p->p->posy += (p->map[(int)(p->p->posy + (p->p->diry * MS *\
						2))][(int)p->p->posx].north <= 0 ? p->p->diry * MS : 0);
		p->p->posx += (p->map[(int)p->p->posy][(int)(p->p->posx + (p->p->dirx * MS *\
						2))].north <= 0 ? p->p->dirx * MS : 0);
	}
	if (p->down == 1)
	{
		p->p->posy -= (p->map[(int)(p->p->posy - (p->p->diry *\
						MS))][(int)p->p->posx].north <= 0 ? p->p->diry * MS : 0);
		p->p->posx -= (p->map[(int)p->p->posy][(int)(p->p->posx - (p->p->dirx *\
						MS))].north <= 0 ? p->p->dirx * MS : 0);
	}
	move_2(p);
	if (p->up == 1 || p->down == 1 || p->right == 1 || p->left == 1)
		ft_display(p);
	return (0);
}
