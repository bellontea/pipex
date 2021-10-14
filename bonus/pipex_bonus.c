/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:52:08 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:31:42 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_open_file2(t_info *info, char **argv, int argc, int *flag)
{
	info->fd2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (info->fd2 < 0)
		perror(argv[argc - 1]);
	*flag = 1;
	info->fd1 = -1;
}

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		*end;
	pid_t	*child;
	char	**all_paths;
	int		flag;

	if (argc < 5)
		return (1);
	flag = 0;
	info.envp = envp;
	if (ft_strncmp("here_doc", argv[1], ft_strlen("here_doc")) == 0)
		ft_open_file2(&info, argv, argc, &flag);
	else
		ft_open_files(&info, argc, argv);
	ft_fill_info(&info, argv, argc, flag);
	all_paths = ft_get_paths(envp);
	child = malloc(sizeof(pid_t) * info.size);
	end = malloc(sizeof(int) * ((info.size - 1) * 2));
	ft_pipex(info, end, child, all_paths);
	ft_wait(child, info.size);
	free(child);
	free(end);
	free(info.cmds);
	ft_free_array(all_paths);
	return (0);
}
