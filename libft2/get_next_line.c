/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 19:59:49 by baparis           #+#    #+#             */
/*   Updated: 2017/05/05 15:36:14 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	check_line(char **line, char *stat)
{
	char	*end;

	end = ft_strchr(stat, '\n');
	if (end != NULL)
	{
		*end = '\0';
		*line = ft_strdup(stat);
		ft_memmove(stat, &end[1], ft_strlen(&end[1]) + 1);
		return (1);
	}
	if (ft_strlen(stat) > 0)
	{
		*line = ft_strdup(stat);
		*stat = '\0';
		return (1);
	}
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*stat = NULL;
	int			ret;
	char		buf[BUFF_SIZE + 1];
	char		*tmp;

	if (!line || fd < 0)
		return (-1);
	if (stat == NULL)
		stat = ft_strnew(0);
	while (!ft_strchr(stat, '\n'))
	{
		ret = read(fd, buf, BUFF_SIZE);
		if (ret == -1)
			return (-1);
		if (ret == 0)
			break ;
		buf[ret] = '\0';
		tmp = ft_strjoin(stat, buf);
		ft_strdel(&stat);
		stat = tmp;
	}
	return (check_line(line, stat));
}
