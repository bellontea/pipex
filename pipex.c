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

int ft_execute_cmd(int fd, char *cmd, char **all_paths)
{
	if (ft_parse_cmd(&cmd, all_paths))
		return (1);
	dup2(fd, 0);
}

int	main(int argc, char **argv, char **envp)
{
	int	end[2];
	int f1;
	int f2;
	t_info	info;
	pid_t	*child;
	char	**all_paths;

	ft_fill_info(&info, argv, argc);
	all_paths = ft_get_paths(envp);
	f1 = open(info.file1, O_RDONLY);
	f2 = open(info.file2, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (f1 < 0 || f2 < 0)
        return (1);
	child = malloc(sizeof(pid_t) * (argc - 3));
	pipe(end);
	child[0] = fork();
	if (child[0] < 0)
        return (perror("Fork: "));
	
	close(end[0]);
    close(end[1]);
}