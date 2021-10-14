/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:34:59 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:35:00 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	const unsigned char		*s = src;

	d = dst;
	if (!d && !s)
		return (dst);
	if (s < d)
	{
		s += len - 1;
		d += len - 1;
		while (len)
		{
			*d-- = *s--;
			len--;
		}
	}
	else
	{
		while (len)
		{
			*d++ = *s++;
			len--;
		}
	}
	return (dst);
}
