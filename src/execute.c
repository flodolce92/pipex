/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:55 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/27 20:34:47 by flo-dolc         ###   ########.fr       */
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

char	**get_env_paths(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	paths = NULL;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			break ;
		}
		i++;
	}
	return (paths);
}

char	*get_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	paths = get_env_paths(envp);
	i = 0;
	while (paths[i++])
	{
		path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(path, cmd);
		if (access(path, F_OK) == 0)
		{
			free_arr(paths);
			return (path);
		}
		free(path);
	}
	free_arr(paths);
	return (NULL);
}

void	exec_cmd(char *arg, char **envp)
{
	char	*path;
	char	**cmd_args;

	ft_putstr_fd("arg = ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\n", 2);
	cmd_args = ft_split_v2(arg, ' ');
	ft_putstr_fd("cmd_args[0] = ", 2);
	ft_putstr_fd(cmd_args[0], 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd("cmd_args[1] = ", 2);
	ft_putstr_fd(cmd_args[1], 2);
	ft_putstr_fd("\n", 2);
	path = get_path(cmd_args[0], envp);
	if (path == NULL)
	{
		free_arr(cmd_args);
		print_error("command not found", 1);
	}
	execve(path, cmd_args, envp);
	print_error("execve failed", 1);
}
