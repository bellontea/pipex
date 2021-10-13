/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:01:17 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/13 20:34:51 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

void	ft_define_fds(t_info *info, int i, int *end)
{
	if (i - 3 < 0)
		info->in = info->fd1;
	else
		info->in = end[i - 3];
	if ((i - 1) / 2 == info->size - 1)
		info->out = info->fd2;
	else
		info->out = end[i];
	if (i - 2 >= 0)
		close(end[i - 2]);
	if ((i - 1) / 2 != info->size - 1)
		close(end[i - 1]);
}

void	ft_close(int *end, t_info info, int i)
{
	if (i == 0)
	{
		if (info.fd1 != -1)
			close(info.fd1);
	}	
	else
	{
		close(end[i * 2 - 1]);
		close(end[i * 2 - 2]);
	}
	if (i == info.size - 1 && info.fd2 != -1)
		close(info.fd2);
}

void	ft_wait(pid_t *child, int size)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (i < size)
	{
		if (child[i] != -2)
			waitpid(child[i], &status, 0);
		i++;
	}
}

void	ft_execute_child(t_info *info, int i, int *end, char **all_paths)
{
	if (i == 0 && info->limiter)
	{
		ft_here_doc(info, end);
		exit(0);
	}
	ft_define_fds(info, i * 2 + 1, end);
	if (ft_execute_cmd(*info, i, all_paths) == 1)
		ft_error(*info, i);
	close(info->in);
	close(info->out);
	exit(0);
}

void	ft_pipex(t_info info, int *end, pid_t *child, char **all_paths)
{
	int	i;

	i = 0;
	while (i < info.size)
	{
		if (i != info.size - 1)
			pipe(end + i * 2);
		child[i] = -2;
		if (info.fd1 == -1)
		{
			i++;
			continue ;
		}
		child[i] = fork();
		if (child[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		if (child[i] == 0)
			ft_execute_child(&info, i, end, all_paths);
		ft_close(end, info, i);
		i++;
	}
}
