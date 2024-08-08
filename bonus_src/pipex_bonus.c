/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciusca <ciusca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:20:09 by ciusca            #+#    #+#             */
/*   Updated: 2024/04/09 19:32:20 by ciusca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_read_heredoc(char **argv, int fds[2])
{
	char	*line;
	char	*limiter;

	line = get_next_line(0);
	close(fds[0]);
	while (line)
	{
		limiter = ft_strjoin(argv[2], "\n");
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			free(limiter);
			close(fds[1]);
			exit(0);
		}
		free(limiter);
		write (fds[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(0);
	}
	free(line);
}

void	ft_here_doc(char **argv, int argc, t_args *pipex)
{
	int		fds[2];
	int		pid;

	if (argc < 6)
		exit (1);
	if (pipe(fds) == -1)
		exit (1);
	pipex->argc = argc;
	pipex->i = 2;
	pid = fork();
	if (pid == 0)
		ft_read_heredoc(argv, fds);
	else
	{
		close(fds[1]);
		dup2(fds[0], STDIN_FILENO);
		wait(NULL);
	}
	pipex->file.out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->file.out < 0)
	{
		perror("[-]");
		exit (1);
	}
	close(fds[0]);
}

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

int	main(int argc, char **argv, char **envp)
{
	char	**path;
	t_args	pipex;
	int		i;

	if (argc < 5)
		return (0);
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		ft_here_doc(argv, argc, &pipex);
	else if (manage_files(argv, argc, &pipex) == -1)
		return (1);
	i = get_envp(envp, &pipex);
	if (i == -1)
		return (1);
	path = ft_split(envp[i], ':');
	if (!path)
		return (0);
	pipex.cmd_path = ft_calloc(sizeof(char *), argc - 2);
	if (!pipex.cmd_path)
		return (1);
	if (check_command(argv, path, &pipex) == 0)
		free_things(&pipex, path, 1);
	free_matrix(path);
	execute_command(&pipex);
	return (0);
}
