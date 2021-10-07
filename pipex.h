#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"

typedef struct s_info
{
	char	*file1;
	char	*file2;
	char	**cmds;
}					t_info;

void	ft_fill_info(t_info *info, char **argv, int argc);

#endif
