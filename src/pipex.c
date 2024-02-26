/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flo-dolc <flo-dolc@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 08:25:49 by flo-dolc          #+#    #+#             */
/*   Updated: 2024/02/26 14:37:55 by flo-dolc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_args(int argc, char **argv)
{
	if (argc != 5)
	{
		ft_putstr_fd("Error: wrong number of arguments\n", 2);
		return (1);
	}
	return (0);
}

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
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
			free_paths(paths);
			return (path);
		}
		free(path);
		i++;
	}
	free_paths(paths);
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
	execve(path, cmd_args, envp);
	ft_putstr_fd("Error: execve failed\n", 2);
}

void	create_child(char *arg, char **envp)
{
	int		pipe_fd[2];
	int		pid;
	char	**cmd;

	if (pipe(pipe_fd) == -1)
	{
		ft_putstr_fd("Error: pipe failed\n", 2);
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Error: fork failed\n", 2);
		exit(1);
	}
	if (pid == 0)
	{
		// if child
		close(pipe_fd[READ_END]);
		dup2(pipe_fd[WRITE_END], STDOUT_FILENO);
		close(pipe_fd[WRITE_END]);
		ft_putendl_fd("First command: ", 2);
		exec_cmd(arg, envp);
	}
	else
	{
		// if parent
		close(pipe_fd[WRITE_END]);
		dup2(pipe_fd[READ_END], STDIN_FILENO);
		close(pipe_fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
}
// argv[1] = file1
// argv[2] = cmd1
// argv[3] = cmd2
// argv[4] = file2
int	main(int argc, char **argv, char **envp)
{
	int	infile;
	int	outfile;

	if (check_args(argc, argv))
		return (1);
	// open file1
	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		ft_putstr_fd("Error: open infile failed\n", 2);
		return (1);
	}
	// open file2
	outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (outfile == -1)
	{
		ft_putstr_fd("Error: open outfile failed\n", 2);
		return (1);
	}
	create_child(argv[2], envp);
	ft_putendl_fd("Last command: ", 2);
	dup2(outfile, STDOUT_FILENO);
	exec_cmd(argv[3], envp);
	ft_putstr_fd("Error: execve failed\n", 2);
	return (0);
}
