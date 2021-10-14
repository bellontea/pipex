/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:35:40 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:35:41 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	i = 0;
	if (!*needle)
		return ((char *) haystack);
	while (i < len && needle[i] && haystack[i])
	{
		if (haystack[i] != needle[i])
		{
			haystack++;
			i = -1;
			len--;
		}
		i++;
	}
	if (!needle[i])
		return ((char *) haystack);
	return (NULL);
}
