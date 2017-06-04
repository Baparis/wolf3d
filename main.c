/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/02 13:41:17 by baparis           #+#    #+#             */
/*   Updated: 2017/06/02 18:01:25 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	ft_exit(t_para *para)
{
	mlx_destroy_window(para->mlx_ptr, para->win_ptr);
	free(para->ima);
	free(para);
	system("killall afplay");
	exit(0);
	return (0);
}

int	ft_run(t_para *par)
{
	system("killall afplay");
	ft_display(par);
	mlx_hook(par->win_ptr, 2, 1, ft_key_rec, par);
	mlx_hook(par->win_ptr, 3, 1, ft_key_release, par);
	mlx_hook(par->win_ptr, 17, 0, ft_exit, par); //red cross
	mlx_loop_hook(par->mlx_ptr, move, par);
	system("afplay Sounds/download.mp3&");
	return (1);
}

int	main(int ac, char **av)
{
	t_map	**map;
	t_para	*para;

	(void)map;
	if (ac < 2)
	{
		ft_putstr("Not enough arguments.\n");
		return (0);
	}
	else
		para = ft_mlx_init(av[1]);
	if (ft_run(para) == 1)
		mlx_loop(para->mlx_ptr);
	return (0);
}
