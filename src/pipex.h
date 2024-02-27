/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:27:16 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/27 20:11:36 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include <sys/types.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"

# define READ_END 0
# define WRITE_END 1

void	print_error(char *msg, int exit_code);
void	create_child(char *arg, char **envp);
void	exec_cmd(char *arg, char **envp);
char	*get_path(char *cmd, char **envp);
void	free_arr(char **arr);
char	**ft_split_v2(const char *str, char c);

#endif
