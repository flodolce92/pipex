/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 21:46:56 by flo-dolc         ###   ########.fr       */
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

// argc = 5, argv = ["pipex", "infile", "cmd1", "cmd2", "outfile"]
// argc = 6, argv = ["pipex", "here_doc", "LIMITER", "cmd1", "cmd2", "outfile"]
// make && ./pipex infile "wc -l" "grep 3" outfile && cat outfile
// make && ./pipex here_doc LIMITER "ls" "grep Make" outfile && cat outfile
int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;
	char	*line;

	if (argc < 5)
		print_error("wrong number of arguments", 1);
	if (argc == 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (outfile == -1)
			print_error("open outfile failed", -1);
		// leggi stdin fino a che non trovi argv[2]
		line = get_next_line(0);
		while (line && ft_strncmp(line, argv[2], ft_strlen(argv[2])) != 0)
		{
			ft_putstr_fd(line, outfile);
			ft_putstr_fd("\n", outfile);
			free(line);
			line = get_next_line(0);
		}
		ft_putstr_fd("leggi stdin fino a che non trovi argv[2]\n", 2);
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
