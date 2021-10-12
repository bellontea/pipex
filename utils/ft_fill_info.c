/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:41:41 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/12 18:06:07 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_fill_info(t_info *info, char **argv, int argc, int flag)
{
	int	i;

	info->size = argc - 3;
	info->cmds = malloc(sizeof(char *) * (info->size + 1));
	i = 0;
	while (i < info->size)
	{
		info->cmds[i] = argv[i + 2];
		i++;
	}
	info->cmds[i] = NULL;
	info->limiter = NULL;
	info->in = 0;
	info->out = 0;
	if (flag)
		info->limiter = info->cmds[0];
}
