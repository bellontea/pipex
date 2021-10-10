#include <pipex.h>

void free_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**ft_get_paths(char **envp)
{
	int i;
	char **all_paths;
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

int ft_parse_cmd(char **cmd, char **all_paths)
{
	int 	i;
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

int ft_execute_cmd(t_info info, int i, char **all_paths, char **envp)
{
	char	**cmd_splitted;

	cmd_splitted = ft_split(info.cmds[i], ' ');
	if (access(cmd_splitted[0], F_OK) && ft_parse_cmd(&(cmd_splitted[0]), all_paths))
	{
		free_array(cmd_splitted);
		return (1);
	}
	dup2(info.in, 0);
	dup2(info.out, 1);
	if (info.in != -1 && info.out != -1)
	{
		if (execve(cmd_splitted[0], cmd_splitted, envp))
			perror(cmd_splitted[0]);
	}
	free_array(cmd_splitted);
	return (0);
}

void	ft_error(t_info info, int i)
{
	ft_putstr_fd(PROGRAM_NAME, 2);
	ft_putstr_fd(": command not found: ", 2);
	ft_putstr_fd(info.cmds[i], 2);
	ft_putstr_fd("\n", 2);
}

int ft_open_files(t_info *info, int argc, char **argv)
{
	info->fd1 = open(argv[1], O_RDONLY);
	if (info->fd1 < 0)
		perror(argv[1]);
	info->fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info->fd2 < 0)
		perror(argv[argc - 1]);
	return (0);
}

void pipex(t_info *info, int i, int *end)
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
	if ((i - 1) / 2 < info->size - 1)
		close(end[i - 1]);
}

int	main(int argc, char **argv, char **envp)
{
	int	*end;
	t_info	info;
	pid_t	*child;
	char	**all_paths;
	int status;
	int i;

	status = 0;
	ft_open_files(&info, argc, argv);
	ft_fill_info(&info, argv, argc);
	all_paths = ft_get_paths(envp);
	child = malloc(sizeof(pid_t) * (argc - 3));
	end = malloc(sizeof(int) * ((info.size) * 2));
	i = 0;
	while (i < info.size)
	{
		if (i != info.size - 1)
			pipe(end + i * 2);
		child[i] = fork();
		if (child[i] == 0)
		{
			pipex(&info, i * 2 + 1, end);
			if (ft_execute_cmd(info, i, all_paths, envp) == 1)
				ft_error(info, i);
			close(info.in);
			close(info.out);
			return (0);
		}
		//printf("%d\n", waitpid(child[i], &status, 0));
		//close(end[i * 2]);
		if (i > 0)
		{
			close(end[i * 2 - 1]);
			close(end[i * 2 - 2]);
		}
		else
			close(info.fd1);
		//close(end[i * 2 + 1]);
		i++;
		if (i == info.size)
			close(info.fd2);
	}
	i = 0;
	// while (i < info.size  * 2)
	// {
	// 	close(end[i]);
	// 	i++;
	// }
	i = 0;
	 while (i < info.size)
	 {
	 	ft_putstr_fd("aad\n", 1);
	 	waitpid(child[i], &status, 0);
	 	i++;
	 }
	close(info.fd1);
	close(info.fd2);
	free(child);
	free(end);
	free(info.cmds);
	free_array(all_paths);
	return (0);
}