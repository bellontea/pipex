#include <pipex.h>

void	ft_fill_info(t_info *info, char **argv, int argc)
{
	int i;

	info->size = argc - 3;
	info->cmds = malloc(sizeof(char*) * (info->size + 1));
	i = 0;
	while (i < info->size)
	{
		
		info->cmds[i] = argv[i + 2];
		i++;
	}
	info->cmds[i] = NULL;
	info->in = 0;
	info->out = 0;
}
