/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:42:19 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/11 22:51:32 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipex.h>

char	**ft_get_paths(char **envp)
{
	int		i;
	char	**all_paths;
	char	*temp;

	i = 0;
	while (ft_strncmp("PATH", envp[i], 4) != 0)
		i++;
	all_paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (all_paths[i])
	{
		temp = ft_strjoin(all_paths[i], "/");
		free(all_paths[i]);
		all_paths[i] = temp;
		i++;
	}
	return (all_paths);
}

int	ft_parse_cmd(char **cmd, char **all_paths)
{
	int		i;
	char	*full_cmd;

	i = 0;
	while (all_paths[i])
	{
		full_cmd = ft_strjoin(all_paths[i], *cmd);
		if (access(full_cmd, F_OK) == 0)
		{
			free(*cmd);
			*cmd = full_cmd;
			return (0);
		}
		free(full_cmd);
		i++;
	}
	return (1);
}

int	ft_execute_cmd(t_info info, int i, char **all_paths, char **envp)
{
	char	**cmd_splitted;

	cmd_splitted = ft_split(info.cmds[i], ' ');
	if (access(cmd_splitted[0], F_OK)
		&& ft_parse_cmd(&(cmd_splitted[0]), all_paths))
	{
		ft_free_array(cmd_splitted);
		return (1);
	}
	dup2(info.in, 0);
	dup2(info.out, 1);
	if (info.in != -1 && info.out != -1)
	{
		if (execve(cmd_splitted[0], cmd_splitted, envp))
			perror(cmd_splitted[0]);
	}
	ft_free_array(cmd_splitted);
	return (0);
}

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
	close(end[i - 1]);
}

void	ft_close(int *end, t_info info, int i)
{
	if (i == 0)
		close(info.fd1);
	else
	{
		close(end[i * 2 - 1]);
		close(end[i * 2 - 2]);
	}
	if (i == info.size - 1)
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
	// close(end[0]);
	len = ft_strlen(info->limiter);
	line = get_next_line(0);
	while ((ft_strncmp(info->limiter, line, len) != 0) || (line[len] != '\n'))
	{
		free(line);
		line = get_next_line(0);
		write(info->fd1, line, ft_strlen(line));
	}
	close(info->fd1);
	free(line);
}

void	ft_pipex(t_info info, int *end, pid_t *child, char **all_paths, char **envp)
{
	int	i;
	int	in[2];

	i = 0;
	if (info.limiter)
	{
		pipe(in);
		ft_here_doc(&info, in);
	}
	while (i < info.size)
	{
		if (i != info.size - 1)
			pipe(end + i * 2);
		child[i] = fork();
		if (child[i] == 0)
		{
			ft_define_fds(&info, i * 2 + 1, end);
			if (ft_execute_cmd(info, i, all_paths, envp) == 1)
				ft_error(info, i);
			close(info.in);
			close(info.out);
			exit(0);
		}
		ft_close(end, info, i);
		i++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		*end;
	pid_t	*child;
	char	**all_paths;

	//if (argc != 5)
	//	return (1);
	if (ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")) == 0)
	{
		info.fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (info.fd2 < 0)
			perror(argv[argc - 1]);
		ft_fill_info(&info, argv + 1, argc, 1);
	}
	else
	{
		ft_open_files(&info, argc, argv);
		ft_fill_info(&info, argv, argc, 0);
	}
	all_paths = ft_get_paths(envp);
	child = malloc(sizeof(pid_t) * (argc - 3));
	end = malloc(sizeof(int) * ((info.size - 1) * 2));
	ft_pipex(info, end, child, all_paths, envp);
	ft_wait(child, info.size);
	free(child);
	free(end);
	free(info.cmds);
	ft_free_array(all_paths);
	return (0);
}
