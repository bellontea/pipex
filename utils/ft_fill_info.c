#include <pipex.h>

void	ft_fill_info(t_info *info, char **argv, int argc)
{
	int i;

	info->file1 = argv[1];
	info->file2 = argv[argc - 1];
	info->cmds = malloc(sizeof(char*) * (argc - 3));
	i = 0;
	while (i < argc - 3)
	{
		info->cmds[i] = argv[i + 2];
		i++;
	}
	info->fd1 = 0;
	info->fd2 = 0;
	info->in = 0;
	info->out = 0;
}
