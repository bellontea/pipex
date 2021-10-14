/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 19:37:34 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 17:08:55 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_here_doc(t_info *info, int *end)
{
	char	*line;
	int		len;

	line = NULL;
	info->fd1 = end[1];
	close(end[0]);
	len = ft_strlen(info->limiter);
	ft_putstr_fd("> ", 1);
	line = get_next_line(0);
	while (line)
	{
		if ((ft_strncmp(info->limiter, line, len) == 0) && (line[len] == '\n'))
			break ;
		write(info->fd1, line, ft_strlen(line));
		ft_putstr_fd("> ", 1);
		free(line);
		line = get_next_line(0);
	}
	close(info->fd1);
	if (line)
		free(line);
}
