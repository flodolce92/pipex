/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:19 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/29 04:57:45 by flo-dolc         ###   ########.fr       */
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

void	delete_tmp_file(int argc, char **argv, char *infile_name)
{
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		unlink(infile_name);
}

void	write_here_doc(char *limiter, char *infile_name)
{
	char	*line;
	int		infile;

	line = NULL;
	infile = open(infile_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		print_error("create infile failed", -1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			print_error("failed to read line", 1);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, infile);
		free(line);
	}
	close(infile);
}
