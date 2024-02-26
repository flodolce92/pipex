/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 15:00:22 by flo-dolc         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (argc < 5)
		print_error("wrong number of arguments", 1);
	// open file1
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		print_error("open infile failed", -1);
	// open file2
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		print_error("open outfile failed", -1);
	create_child(argv[2], envp);
	ft_putendl_fd("Last command: ", 2);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(argv[3], envp);
	ft_putstr_fd("Error: execve failed\n", 2);
	return (0);
}
