/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:19 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 15:18:11 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	create_child(char *arg, char **envp)
{
	int		pipe_fd[2];
	int		pid;

	if (pipe(pipe_fd) == -1)
		print_error("pipe failed", -1);
	pid = fork();
	if (pid == -1)
		print_error("fork failed", -1);
	if (pid == 0)
	{
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		ft_putendl_fd("First command: ", 2);
		exec_cmd(arg, envp);
	}
	else
	{
		close(pipe_fd[WRITE_END]);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
}
