/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 16:34:01 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:34:03 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	int		sign;
	char	*num;
	int		size;

	sign = 1;
	size = ft_count_size(n);
	if (n < 0)
	{
		size++;
		sign = -1;
	}
	num = malloc(sizeof(char) * size + 1);
	if (!num)
		return (NULL);
	num[size] = '\0';
	size--;
	num[0] = '-';
	num[size] = '0';
	while (n)
	{
		num[size] = '0' + (n % 10) * sign;
		n /= 10;
		size--;
	}
	return (num);
}
