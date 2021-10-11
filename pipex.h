/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mslyther <mslyther@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 13:44:57 by mslyther          #+#    #+#             */
/*   Updated: 2021/10/11 20:13:11 by mslyther         ###   ########.fr       */
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
}					t_info;

void	ft_fill_info(t_info *info, char **argv, int argc, int flag);
void	ft_free_array(char **array);
void	ft_error(t_info info, int i);
int		ft_open_files(t_info *info, int argc, char **argv);

#endif
