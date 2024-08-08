/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:36:15 by ciusca            #+#    #+#             */
/*   Updated: 2024/04/05 16:59:20 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_envp(char **envp, t_args *pipex)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			pipex->envp = envp;
			return (i);
		}
	}
	return (-1);
}

void	set_first(t_args *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->i + 1)
		pipex->argv[i] = ft_strdup("None");
}

int	find_path(char **path, char *cmd, t_args *pipex)
{
	int				i;
	char			*str;
	static int		j;
	char			**mat;

	i = -1;
	while (path[++i])
	{
		str = ft_strjoin(path[i], cmd);
		mat = ft_split(str, 32);
		if (!mat)
			return (-1);
		if (access(mat[0], X_OK) == 0)
		{
			pipex->cmd_path[j] = ft_strdup(mat[0]);
			j++;
			free(str);
			free_matrix(mat);
			return (i);
		}
		free_matrix(mat);
		free(str);
	}
	return (-1);
}

int	check_command(char **argv, char **path, t_args *pipex)
{
	char	*cmd;
	int		i;

	i = pipex->i;
	pipex->argv = ft_calloc(sizeof(char *), pipex->argc);
	set_first(pipex);
	if (!pipex->argv)
		return (0);
	cmd = ft_strdup(path[0]);
	free(path[0]);
	path[0] = ft_strtrim(cmd, "PATH=");
	free(cmd);
	while (++i < pipex->argc - 1)
	{
		if (!ft_strrchr(argv[i], '/'))
			cmd = ft_strjoin("/", argv[i]);
		else
			cmd = argv[i];
		if (find_path(path, cmd, pipex) < 0)
			return (free(cmd), 0);
		pipex->argv[i] = ft_strtrim(cmd, "/");
		free(cmd);
	}
	return (1);
}
