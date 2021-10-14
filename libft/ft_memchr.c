/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:34:52 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:34:53 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str = s;
	const unsigned char	stop = c;

	while (n)
	{
		if (*str == stop)
			return ((unsigned char *)str);
		str++;
		n--;
	}
	return (NULL);
}
