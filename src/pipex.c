/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/29 04:16:58 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int exit_code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(exit_code);
}

void	write_here_doc(char *limiter)
{
	char	*line;
	int		infile;

	line = NULL;
	infile = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (infile == -1)
		print_error("open infile failed", -1);
	while (1)
	{
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			print_error("readline failed", 1);
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

// argc = 5, argv = ["pipex", "infile", "cmd1", "cmd2", "outfile"]
// argc = 6, argv = ["pipex", "here_doc", "LIMITER", "cmd1", "cmd2", "outfile"]
// make && ./pipex infile "wc -l" "grep 3" outfile && cat outfile
// make && ./pipex here_doc LIMITER "ls" "grep Make" outfile && cat outfile
int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;

	i = 0;
	if (argc < 5)
		print_error("wrong number of arguments", 1);
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		write_here_doc(argv[2]);
		infile = open(".here_doc", O_RDONLY);
		if (infile == -1)
			print_error("open infile failed", -1);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			print_error("open outfile failed", -1);
		dup2(infile, STDIN_FILENO);
	}
	else
	{
		i = 2;
		infile = open(argv[1], O_RDONLY);
		if (infile == -1)
			print_error("open infile failed", -1);
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (outfile == -1)
			print_error("open outfile failed", -1);
		dup2(infile, STDIN_FILENO);
	}
	while (i < argc - 2)
	{
		create_child(argv[i], envp);
		i++;
	}
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(argv[argc - 2], envp);
	print_error("execve failed", 1);
	return (0);
}
