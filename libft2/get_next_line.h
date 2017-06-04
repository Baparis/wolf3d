/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 14:28:38 by baparis           #+#    #+#             */
/*   Updated: 2017/04/15 07:52:13 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 2056

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

int		get_next_line(const int fd, char **line);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
void	ft_strdel(char **as);
char	*ft_strdup(const char *s);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);

#endif
