/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:44:57 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/12 20:18:48 by mslyther         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "get_next_line.h"
# include <sys/wait.h>
# include <string.h>

# define PROGRAM_NAME "pipex"

typedef struct s_info
{
	int		fd1;
	int		fd2;
	int		in;
	int		out;
	char	**cmds;
	int		size;
	char	*limiter;
	char	**envp;
}					t_info;

void	ft_fill_info(t_info *info, char **argv, int argc, int flag);
void	ft_free_array(char **array);
void	ft_error(t_info info, int i);
int		ft_open_files(t_info *info, int argc, char **argv);
void	ft_define_fds(t_info *info, int i, int *end);
char	**ft_get_paths(char **envp);
int		ft_parse_cmd(char **cmd, char **all_paths);
int		ft_execute_cmd(t_info info, int i, char **all_paths);
void	ft_define_fds(t_info *info, int i, int *end);
void	ft_close(int *end, t_info info, int i);
void	ft_wait(pid_t *child, int size);
void	ft_pipex(t_info info, int *end, pid_t *child, char **all_paths);
void	ft_here_doc(t_info *info, int *end);

#endif
