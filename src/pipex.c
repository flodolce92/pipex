/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2025/09/22 03:30:30 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(char *msg, int exit_code)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(msg, 2);
	if (errno != 0)
	{
		ft_putstr_fd(": ", 2);
		perror("");
	}
	else
		ft_putstr_fd("\n", 2);
	unlink(".here_doc");
	if (exit_code != -1)
		exit(exit_code);
}

void	check_here_doc(int argc, char **argv, t_pipex *pipex, int *i)
{
	if (argc >= 6 && ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		(*i) = 3;
		pipex->flags = O_WRONLY | O_CREAT | O_APPEND;
		pipex->infile_name = ".here_doc";
		write_here_doc(argv[2], pipex->infile_name);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_pipex	pipex;

	i = 2;
	pipex.infile_name = argv[1];
	pipex.flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (argc < 5)
		print_error("wrong number of arguments", 1);
	check_here_doc(argc, argv, &pipex, &i);
	if (!open_files(&pipex, argc, argv))
		return (1);
	while (i < argc - 2)
	{
		create_child(argv[i], envp);
		i++;
	}
	last_command(argc, argv, envp, pipex);
	return (0);
}
