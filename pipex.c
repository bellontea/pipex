/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:42:19 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:08:52 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_info	info;
	int		*end;
	pid_t	*child;
	char	**all_paths;

	if (argc != 5)
		return (1);
	info.envp = envp;
	ft_open_files(&info, argc, argv);
	ft_fill_info(&info, argv, argc, 0);
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
