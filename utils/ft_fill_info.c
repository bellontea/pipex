#include <pipex.h>

void	ft_fill_info(t_info *info, char **argv, int argc)
{
	int i;

	info->cmds = malloc(sizeof(char*) * (argc - 2));
	i = 0;
	while (i < argc - 3)
	{
		
		info->cmds[i] = argv[i + 2];
		i++;
	}
	info->cmds[i] = NULL;
	info->in = 0;
	info->out = 0;
}
