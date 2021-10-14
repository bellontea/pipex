/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:34:46 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:34:47 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s = src;
	const unsigned char	stop = c;
	size_t				i;

	d = dst;
	if (!n)
		return (NULL);
	i = 0;
	while (i < n - 1 && s[i] != stop)
	{
		d[i] = s[i];
		i++;
	}
	d[i] = s[i];
	if (s[i] != stop)
		return (NULL);
	else
		return (d + i + 1);
}
