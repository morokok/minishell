/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 20:12:52 by tjmari            #+#    #+#             */
/*   Updated: 2021/05/30 16:57:09 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(int i)
{
	char	**temp;
	int		nodes;

	temp = ft_dcdup(g_tool.envp, 0);
	nodes = how_many_element(g_tool.cmd[i]->args);
	if (nodes == 1)
	{
		sortdcp(temp);
		ft_putexport(temp);
	}
	else
		g_tool.envp = add_node_dc(g_tool.envp, g_tool.cmd[i]->args, nodes);
}

void	ft_putexport(char **argv)
{
	int		i;
	char	**parts;

	i = 0;
	while (argv[i])
	{
		parts = ft_split(argv[i++], '=');
		if (parts[1])
			printf("declare -x %s=\"%s\"\n", parts[0], parts[1]);
		else
			printf("declare -x %s=\"\"\n", parts[0]);
	}
}

char	*ft_getkey(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (ft_substr(arg, 0, i));
		i++;
	}
	return (arg);
}

char	*ft_getvalue(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '=')
			return (ft_substr(arg, i + 1, ft_strlen(arg)));
		i++;
	}
	return (ft_strdup(""));
}