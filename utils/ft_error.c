/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:49:42 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/11 13:49:59 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_error(t_info info, int i)
{
	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putstr_fd(info.cmds[i], 2);
	ft_putstr_fd("\n", 2);
}
