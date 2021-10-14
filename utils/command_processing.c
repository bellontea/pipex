/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_processing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 19:58:11 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/14 16:08:32 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

	if ((cmd[0][0] == '/' || (cmd[0][0] == '.' && cmd[0][1] == '/'))
		&& !access(cmd[0], F_OK))
		return (0);
	i = 0;
	while (all_paths[i])
	{
		full_cmd = ft_strjoin(all_paths[i], cmd[0]);
		if (access(full_cmd, F_OK) == 0)
		{
			free(cmd[0]);
			cmd[0] = full_cmd;
			return (0);
		}
		free(full_cmd);
		i++;
	}
	return (1);
}

int	ft_execute_cmd(t_info info, int i, char **all_paths)
{
	char	**cmd_splitted;

	cmd_splitted = ft_split(info.cmds[i], ' ');
	if (ft_parse_cmd(cmd_splitted, all_paths))
	{
		ft_free_array(cmd_splitted);
		return (1);
	}
	dup2(info.in, 0);
	dup2(info.out, 1);
	if (info.in != -1 && info.out != -1)
	{
		if (execve(cmd_splitted[0], cmd_splitted, info.envp))
			perror(cmd_splitted[0]);
	}
	ft_free_array(cmd_splitted);
	return (0);
}
