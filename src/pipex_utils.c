/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:19 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/29 05:38:10 by flo-dolc         ###   ########.fr       */
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

void	delete_tmp_file(char *infile_name)
{
	if (unlink(infile_name) == -1)
		print_error("unlink failed", -1);
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

void	open_files(t_pipex *pipex, int argc, char **argv)
{
	pipex->infile = open(pipex->infile_name, O_RDONLY);
	if (pipex->infile == -1)
		print_error("open infile failed", -1);
	pipex->outfile = open(argv[argc - 1], pipex->flags, 0644);
	if (pipex->outfile == -1)
		print_error("open outfile failed", -1);
	dup2(pipex->infile, STDIN_FILENO);
}

void	last_command(int argc, char **argv, char **envp, t_pipex pipex)
{
	close(pipex.infile);
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
		delete_tmp_file(pipex.infile_name);
	dup2(pipex.outfile, STDOUT_FILENO);
	exec_cmd(argv[argc - 2], envp);
	print_error("execve failed", 1);
}
