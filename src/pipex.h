/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:27:16 by flo-dolc          #+#    #+#             */
/*   Updated: 2025/09/22 03:30:12 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

# define READ_END 0
# define WRITE_END 1

typedef struct s_pipex
{
	int		infile;
	int		outfile;
	int		flags;
	char	*infile_name;
}	t_pipex;

void	print_error(char *msg, int exit_code);
void	create_child(char *arg, char **envp);
void	exec_cmd(char *arg, char **envp);
char	*get_path(char *cmd, char **envp);
void	free_arr(char **arr);
char	**ft_split_v2(const char *str, char c);
void	delete_tmp_file(char *infile_name);
void	write_here_doc(char *limiter, char *infile_name);
bool	open_files(t_pipex *pipex, int argc, char **argv);
void	last_command(int argc, char **argv, char **envp, t_pipex pipex);

#endif
