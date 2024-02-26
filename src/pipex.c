/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 16:06:39 by flo-dolc         ###   ########.fr       */
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
	int	i;
	int	infile;
	int	outfile;

	i = 2;
	if (argc < 5)
		print_error("wrong number of arguments", 1);
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
		print_error("open infile failed", -1);
	outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
		print_error("open outfile failed", -1);
	dup2(infile, STDIN_FILENO);
	while (i < argc - 2)
	{
		create_child(argv[i], envp);
		i++;
	}
	ft_putendl_fd("Last command: ", 2);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(argv[argc - 2], envp);
	print_error("execve failed", 1);
	return (0);
}
