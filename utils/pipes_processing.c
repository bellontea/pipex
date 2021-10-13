/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 20:01:17 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/13 17:09:34 by mslyther         ###   ########.fr       */
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
		waitpid(child[i], &status, 0);
		i++;
	}
}

void	ft_here_doc(t_info *info, int *end)
{
	char	*line;
	int		len;

	line = NULL;
	info->fd1 = end[1];
	close(end[0]);
	len = ft_strlen(info->limiter);
	line = get_next_line(0);
	while (line)
	{
		if ((ft_strncmp(info->limiter, line, len) == 0) && (line[len] == '\n'))
			break ;
		write(info->fd1, line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	close(info->fd1);
	if (line)
		free(line);
}

void	ft_pipex(t_info info, int *end, pid_t *child, char **all_paths)
{
	int	i;

	i = 0;
	while (i < info.size)
	{
		if (i != info.size - 1)
			pipe(end + i * 2);
		if (info.fd1 == -1)
		{
			i++;
			continue ;
		}
		child[i] = fork();
		if (child[i] == 0)
		{
			if (i == 0 && info.limiter)
			{
				ft_here_doc(&info, end);
				exit(0);
			}
			ft_define_fds(&info, i * 2 + 1, end);
			if (ft_execute_cmd(info, i, all_paths) == 1)
				ft_error(info, i);
			if (info.in != -1)
				close(info.in);
			if (info.out != -1)
				close(info.out);
		}
		ft_close(end, info, i);
		i++;
	}
}
