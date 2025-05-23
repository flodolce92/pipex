/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:44:55 by flo-dolc          #+#    #+#             */
/*   Updated: 2025/05/04 22:24:55 by flo-dolc         ###   ########.fr       */
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
	char	*tmp;
	int		i;

	paths = get_env_paths(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		free(tmp);
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

	cmd_args = ft_split_v2(arg, ' ');
	path = get_path(cmd_args[0], envp);
	if (path == NULL)
	{
		free_arr(cmd_args);
		print_error("command not found", 1);
	}
	execve(path, cmd_args, envp);
	print_error("execve failed", 1);
}
