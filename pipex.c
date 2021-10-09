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

int	main(int argc, char **argv, char **envp)
{
	int	end[2];
	t_info	info;
	pid_t	*child;
	char	**all_paths;
	int status;

	info.fd1 = open(argv[1], O_RDONLY);
	if (info.fd1 < 0)
		perror(argv[1]);
	info.fd2 = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info.fd2 < 0)
		perror(argv[argc - 1]);
	ft_fill_info(&info, argv, argc);
	all_paths = ft_get_paths(envp);
	child = malloc(sizeof(pid_t) * (argc - 3));
	pipe(end);
	child[0] = fork();
	if (child[0] < 0)
	{
		perror("Fork: ");
		return (1);
	}
	if (child[0] == 0)
	{
		info.in = info.fd1;
		info.out = end[1];
		if (ft_execute_cmd(info, 0, all_paths, envp) == 1)
			ft_error(info, 0);
		close(info.fd1);
    	close(end[1]);
		close(end[0]);
		return (0);
//		close(end[0]);
	}
	child[1] = fork();
	if (child[1] < 0)
    {
		perror("Fork: ");
		return (1);
	}
	if (child[1] == 0)
	{
		info.in = end[0];
		info.out = info.fd2;
    	close(end[1]);
		if (ft_execute_cmd(info, 1, all_paths, envp) == 1)
			ft_error(info, 1);
		close(info.fd2);
		close(end[0]);
		return (0);
//		close(end[0]);
	}
	close(end[0]);
    close(end[1]);
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	free(child);
	free(info.cmds);
	free_array(all_paths);
	return (0);
}