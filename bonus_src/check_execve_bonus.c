/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_execve_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:58:18 by ciusca            #+#    #+#             */
/*   Updated: 2024/04/05 16:57:19 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_child(char *path, t_args *pipex, char **commands, int pid)
{
	int	saved_out;

	if (pid == 0)
	{
		saved_out = dup(1);
		close(pipex->fds[0]);
		dup2(pipex->fds[1], STDOUT_FILENO);
		if (execve(path, commands, pipex->envp) == -1)
			return (-1);
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
	else
	{
		close(pipex->fds[1]);
		dup2(pipex->fds[0], STDIN_FILENO);
		waitpid(pid, 0, 0);
	}
	return (1);
}

int	last_command(t_args *pipex, char **commands, int j)
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		dup2(pipex->file.out, STDOUT_FILENO);
		if (execve(pipex->cmd_path[j], commands, pipex->envp) == -1)
			return (-1);
	}
	return (1);
}

int	execute_command(t_args *pipex)
{
	char	**commands;
	int		pid;
	int		j;
	int		i;

	i = pipex->i;
	j = 0;
	while (++i < pipex->argc - 2)
	{
		pipe(pipex->fds);
		commands = ft_split(pipex->argv[i], 32);
		pid = fork();
		if (ft_child(pipex->cmd_path[j], pipex, commands, pid) == -1)
			free_things(pipex, commands, 1);
		j++;
		free_matrix(commands);
	}
	close (pipex->fds[0]);
	commands = ft_split(pipex->argv[i], 32);
	if (last_command(pipex, commands, j) == -1)
		free_things(pipex, commands, 1);
	close(pipex->file.out);
	free_things(pipex, commands, 0);
	return (1);
}

int	manage_files(char **argv, int argc, t_args *pipex)
{
	pipex->file.inf = open(argv[1], __O_DIRECTORY);
	if (pipex->file.inf > 0)
	{
		close(pipex->file.inf);
		return (-1);
	}
	pipex->file.inf = open(argv[1], O_RDONLY, 0777);
	if (pipex->file.inf < 0)
	{
		perror("[-]");
		return (-1);
	}
	pipex->file.out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->file.out < 0)
	{
		close(pipex->file.inf);
		perror("[-]");
		return (-1);
	}
	pipex->argc = argc;
	dup2(pipex->file.inf, 0);
	close(pipex->file.inf);
	pipex->i = 1;
	return (1);
}
