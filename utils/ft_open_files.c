/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:50:58 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:08:18 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_open_files(t_info *info, int argc, char **argv)
{
	info->fd1 = open(argv[1], O_RDONLY);
	if (info->fd1 < 0)
		perror(argv[1]);
	info->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (info->fd2 < 0)
		perror(argv[argc - 1]);
	return (0);
}
