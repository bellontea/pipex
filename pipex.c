#include <pipex.h>

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
		if (access(full_cmd, X_OK) == 0)
		{
			free(*cmd);
			*cmd = full_cmd;
			return (0);
		}
		i++;
	}
	return (1);
}

int ft_execute_cmd(t_info info, int i, char **all_paths, char **envp)
{
	char	**cmd_splitted;

	cmd_splitted = ft_split(info.cmds[i], ' ');
	if (ft_parse_cmd(&(cmd_splitted[0]), all_paths))
		return (1);
	dup2(info.in, 0);
	dup2(info.out, 1);
	execve(cmd_splitted[0], cmd_splitted, envp);
	perror("Error");
	i = 0;
	while (cmd_splitted[i])
	{
		free(cmd_splitted[i]);
		i++;
	}
	free(cmd_splitted);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int	end[2];
	t_info	info;
	pid_t	*child;
	char	**all_paths;
	int status;

	ft_fill_info(&info, argv, argc);
	all_paths = ft_get_paths(envp);
	info.fd1 = open(info.file1, O_RDONLY);
	info.fd2 = open(info.file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (info.fd1 < 0 || info.fd2 < 0)
        return (1);
	child = malloc(sizeof(pid_t) * (argc - 3));
	pipe(end);
	child[0] = fork();
	if (child[0] < 0)
	{
		perror("Fork: 0");
		return (1);
	}
	if (child[0] == 0)
	{
		info.in = info.fd1;
		info.out = end[1];
		ft_execute_cmd(info, 0, all_paths, envp);
		close(info.fd1);
    	close(end[1]);
		close(end[0]);
		return (0);
//		close(end[0]);
	}
	child[1] = fork();
	if (child[1] < 0)
    {
		perror("Fork: 1");
		return (1);
	}
	if (child[1] == 0)
	{
		info.in = end[0];
		info.out = info.fd2;
    	close(end[1]);
		ft_execute_cmd(info, 1, all_paths, envp);
		close(info.fd2);
		close(end[0]);
		return (0);
//		close(end[0]);
	}
	close(end[0]);
    close(end[1]);
	waitpid(child[0], &status, 0);
	waitpid(child[1], &status, 0);
	return (0);
}