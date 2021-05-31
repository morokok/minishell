/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:36 by tjmari            #+#    #+#             */
/*   Updated: 2021/05/31 11:37:28 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	change_pwd(int index, char *arg)
{
	free(g_tool.envp[index]);
	g_tool.envp[index] = ft_strdup(arg);
}

void	ft_cd(int i)
{
	int pwd = get_env("PWD");
	int oldpwd = get_env("OLDPWD");
	if (chdir(g_tool.cmd[i]->args[1]) != 0)
		ft_putendl_fd(strerror(errno), 2);
	else
	{
		if (oldpwd >= 0 && pwd >= 0)
			change_pwd(oldpwd, ft_strjoin("OLDPWD=", ft_getvalue(g_tool.envp[pwd])));
		if (pwd >= 0)
			change_pwd(pwd, ft_strjoin("PWD=", getcwd(g_tool.cwd, sizeof(g_tool.cwd))));
	}
}
