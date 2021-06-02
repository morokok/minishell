/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_infork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:17:14 by tjmari            #+#    #+#             */
/*   Updated: 2021/06/02 16:56:57 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	run_infork(int i)
{
	open_pipe(i);
	g_tool.pid = fork();
	if (!(g_tool.cmd[i]->sep && *(g_tool.cmd[i]->sep) == '|'))
		waitpid(g_tool.pid, &g_tool.exit_status, 0);
	if (WIFSIGNALED(g_tool.exit_status))
		g_tool.exit_status = 128 + WTERMSIG(g_tool.exit_status);
	else
		g_tool.exit_status = WEXITSTATUS(g_tool.exit_status);
	if (g_tool.pid == 0)
	{
		set_pipe(i);
		if (!g_tool.cmd[i]->args && g_tool.cmd[i]->red)		//	> file
		{
			if (!(set_redirections(g_tool.cmd[i])))
				exit(g_tool.exit_status);
			exit(g_tool.exit_status);
		}
		else if (g_tool.which_builtin)						//	builtin
		{
			if (!(set_redirections(g_tool.cmd[i])))
				exit(g_tool.exit_status);
			run_builtin(i);
			exit(g_tool.exit_status);
		}
		else
		{
			if (!(set_redirections(g_tool.cmd[i])))
				exit(g_tool.exit_status);
			cmd_infork(i);
		}
	}
	close(g_tool.cmd[i]->pipe[1]);
	if (i > 0 && g_tool.cmd[i - 1]->sep && *(g_tool.cmd[i - 1]->sep) == '|')
		close(g_tool.cmd[i - 1]->pipe[0]);
}

void	cmd_infork(int i)
{
	char	*path;
	char	**paths;
	char	*cmd;
	int		path_exist;

	path_exist = get_env("PATH");
	if (path_exist > 0)
		path = g_tool.envp[path_exist];
	paths = ft_split(path, ':');
	if (ft_strchr(g_tool.cmd[i]->args[0], '/') || (path_exist < 0))
	{
		execve(g_tool.cmd[i]->args[0], g_tool.cmd[i]->args, g_tool.envp);
		if (!ft_strcmp(g_tool.cmd[i]->args[0], "."))
		{
			ft_putendl_fd("minishell: .: filename argument required", 2);
			ft_putendl_fd(".: usage: . filename [arguments]", 2);
			exit(2);
		}
		execve_failure(i);
	}
	else
	{
		cmd = make_cmd(paths, g_tool.cmd[i]->args[0]);
		if (!ft_strcmp(g_tool.cmd[i]->args[0], "."))
		{
			ft_putendl_fd("minishell: .: filename argument required", 2);
			ft_putendl_fd(".: usage: . filename [arguments]", 2);
			exit(2);
		}
		else if (cmd && ft_strcmp(g_tool.cmd[i]->args[0], ".."))
			execve(cmd, g_tool.cmd[i]->args, g_tool.envp);
		else
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(g_tool.cmd[i]->args[0], 2);
			ft_putendl_fd(": command not found", 2);
			exit(127);
		}
	}
}

char	*make_cmd(char **paths, char *cmd)
{
	int		i;
	char	*temp;

	i = 0;
	while (paths[i])
	{
		temp = ft_strjoin(paths[i], "/");
		temp = ft_strjoin(temp, cmd);
		if (open(temp, O_RDONLY) > 0)
			return (temp);
		i++;
	}
	return (NULL);
}
