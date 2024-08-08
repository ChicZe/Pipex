/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:20:09 by ciusca            #+#    #+#             */
/*   Updated: 2024/04/09 19:33:08 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	free_argv(t_args *pipex, char **argv)
{
	int	i;

	i = 1;
	while (++i < pipex->argc - 1)
		free(argv[i]);
}

void	free_things(t_args *pipex, char **matrix, int ex)
{
	free_matrix(pipex->cmd_path);
	free_matrix(matrix);
	free_matrix(pipex->argv);
	if (ex == 1)
	{
		perror("[-]");
		exit(1);
	}
}

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

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	t_args	pipex;
	int		i;

	if (argc != 5)
		return (0);
	if (manage_files(argv, argc, &pipex) == -1)
		return (1);
	i = get_envp(envp, &pipex);
	if (i == -1)
		return (1);
	path = ft_split(envp[i], ':');
	if (!path)
		return (1);
	pipex.cmd_path = ft_calloc(sizeof(char *), 3);
	if (!pipex.cmd_path)
		return (1);
	if (check_command(argv, path, &pipex) == 0)
		free_things(&pipex, path, 1);
	free_matrix(path);
	execute_command(&pipex);
	return (0);
}
