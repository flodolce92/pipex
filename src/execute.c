/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:55 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 15:17:28 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (paths[i])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_arr(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_arr(paths);
	ft_putstr_fd("Error: command not found\n", 2);
	return (NULL);
}

void	exec_cmd(char *arg, char **envp)
{
	// execute a command
	// execve(path, commands, env)
	char	*path;
	char	**cmd_args;

	cmd_args = ft_split(arg, ' ');
	path = get_path(cmd_args[0], envp);
	if (path == NULL)
	{
		free_arr(cmd_args);
		print_error("command not found", 1);
	}
	execve(path, cmd_args, envp);
	ft_putstr_fd("Error: execve failed\n", 2);
}
