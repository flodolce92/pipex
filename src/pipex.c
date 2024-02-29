/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/29 05:08:49 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int exit_code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	unlink(".here_doc");
	if (errno != 0)
		perror("");
	exit(exit_code);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		infile;
	int		outfile;
	int		flags;
	char	*infile_name;

	i = 2;
	infile_name = argv[1];
	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (argc < 5)
		print_error("wrong number of arguments", 1);
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		flags = O_WRONLY | O_CREAT | O_APPEND;
		infile_name = ".here_doc";
		write_here_doc(argv[2], infile_name);
	}
	infile = open(infile_name, O_RDONLY);
	if (infile == -1)
		print_error("open infile failed", -1);
	outfile = open(argv[argc - 1], flags, 0644);
	if (outfile == -1)
		print_error("open outfile failed", -1);
	dup2(infile, STDIN_FILENO);
	while (i < argc - 2)
	{
		create_child(argv[i], envp);
		i++;
	}
	close(infile);
	delete_tmp_file(argc, argv, infile_name);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(argv[argc - 2], envp);
	print_error("execve failed", 1);
	return (0);
}
