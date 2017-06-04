/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baparis <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/09 16:30:32 by baparis           #+#    #+#             */
/*   Updated: 2016/11/23 15:08:44 by baparis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*dest;
	int		j;

	j = 0;
	i = -1;
	if (!(s1) || !(s2))
		return (0);
	if ((dest = (char*)malloc(sizeof(char) * ft_strlen(s1) + ft_strlen(s2)\
					+ 1)))
	{
		while (s1[++i])
			dest[i] = s1[i];
		while (s2[j])
			dest[i++] = s2[j++];
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}
