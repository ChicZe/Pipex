/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:19:32 by ciusca            #+#    #+#             */
/*   Updated: 2024/03/29 16:31:20 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/wait.h>

typedef struct s_files
{
	int	inf;
	int	out;
}				t_files;

typedef struct s_args
{
	int		i;
	char	**argv;
	char	**envp;
	char	**cmd_path;
	int		argc;
	int		fds[2];
	t_files	file;
}				t_args;

/* bonus */
void	ft_here_doc(char **argv, int argc, t_args *pipex);

/* parsing */
int		check_command(char **argv, char **path, t_args *pipex);
int		get_envp(char **envp, t_args *pipex);

/* managing files */
int		manage_files(char **argv, int argc, t_args *pipex);

/* executing commands */
int		execute_command(t_args *pipex);

/* utils */
void	free_things(t_args *pipex, char **matrix, int ex);

#endif