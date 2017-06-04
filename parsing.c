/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/15 07:52:47 by baparis           #+#    #+#             */
/*   Updated: 2017/05/29 18:20:49 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_error(int error)
{
	if (error == 1)
		ft_putstr("Error reading map, Verify map name and retry\n");
	if (error == 2)
		ft_putstr("Malloc allocation error\n");
	if (error == 3)
		ft_putstr("MLX c'EST DE LA MERDE\n");
	exit(0);
}

t_map	*reader(char *file, t_map *ret)
{
	int		i;
	char	*cpy;

	i = 0;
	cpy = file;
	while (cpy != NULL)
	{
		cpy = cpy + 1;
		ret[i].north = ft_atoi(cpy);
		cpy = ft_strstr(cpy + 1, "[");
		i++;
	}
	free(cpy);
	return (ret);
}

t_map	**filler(int sizex, int sizey, char *path)
{
	t_map	**ret;
	int		fd;
	char	*tab;
	int		i;

	i = 0;
	if (!(fd = open(path, O_RDONLY)))
		ft_error(2);
	if (!(ret = (t_map**)malloc(sizeof(t_map) * sizey)))
		ft_error(2);
	while (get_next_line(fd, &tab))
	{
		if (!(ret[i] = (t_map*)malloc(sizeof(t_map) * sizex)))
			ft_error(2);
		ret[i] = reader(tab, ret[i]);
		free(tab);
		i++;
	}
	return (ret);
}

t_map	**map_loader(char *path, t_para *par)
{
	int		fd;
	char	*file;
	char	*cpy;
	int		sizey;
	int		sizex;

	sizey = 1;
	sizex = 0;
	if (!(fd = open(path, O_RDONLY)) || get_next_line(fd, &file) <= 0)
		ft_error(1);
	cpy = file;
	while (cpy++ && *cpy)
		if (*cpy == ']')
			sizex++;
	free(file);
	while (get_next_line(fd, &file))
	{
		sizey++;
		free(file);
	}
	close(fd);
	par->maxx = sizex - 1;
	par->maxy = sizey - 1;
	return (filler(sizex, sizey, path));
}
