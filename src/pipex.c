/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 09:30:41 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

int	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	(void)argv;
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	int		pid;
	char	**cmd;

	if (check_args(argc, argv))
		return (1);
	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		return (1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		return (1);
	}
	if (pid == 0)
	{
		// close(pipe_fd[READ_END]);
		// dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		// close(pipe_fd[WRITE_END]);
		cmd = ft_split(argv[2], ' ');
		execve(cmd[0], cmd, NULL);
	}
	else
	{
		close(pipe_fd[WRITE_END]);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		waitpid(pid, NULL, 0);
		cmd = ft_split(argv[3], ' ');
		execve(cmd[0], cmd, NULL);
	}
	return (0);
}
