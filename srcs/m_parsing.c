/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmarzouk <mmarzouk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 16:59:17 by tjmari            #+#    #+#             */
/*   Updated: 2021/05/30 17:43:42 by mmarzouk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_cmds(char **s)
{
	int c;
	int i;
	int j;

	i = 0;
	c = 0;
	j = 0;
	while (s && s[i])
	{
		if(((s[i][j])) == '|' || (s[i][j]) == ';')
			c++;
		i++;        
	}
	return(c);
}

static void double_print(char **s)
{
	int i = 0;
	if (!s)
	{
		printf("\033[0;31m(null)\033[0m\n");
		return ;
	}
	while (s[i])
	{
		if (i != 0)
			printf("		");
		printf("%s\n", s[i]);
		i++;
	}
	
}

 void printall(void)
{
	int i = 0;

	while (i < g_tool.cmd_c)
	{
		printf("_________________________\n");
		printf("\033[0;32marg[%d]:		\033[0m",i);
		double_print(g_tool.cmd[i]->args);
		printf("\033[0;32msep[%d]:		\033[0m",i);
		if (g_tool.cmd[i]->sep)
			printf("%s\n", g_tool.cmd[i]->sep);
		else
			printf("\033[0;31m%s\033[0m\n", g_tool.cmd[i]->sep);
		printf("\033[0;32mred[%d]:		\033[0m",i);
		double_print(g_tool.cmd[i]->red);
		printf("\033[0;32mfil[%d]:		\033[0m",i);
		double_print(g_tool.cmd[i]->file);
		printf("_________________________\n");
		i++;
	}
}

int seterr(short err)
{
	if (err)
	{
		g_tool.exterr = err;
		return(1);
	}
	return (0);
}

int parsing(char *s)
{
	char    **sp;
	while(s && *s == ' ')
		s++;
	if(!(sp = split_it(s, NULL, 0, 0)))
	{
		// printf("<%d>SPLIT\n",g_tool.exterr);
		return(0);
	}
	if (seterr(chk_err(sp, 0, 0, 0)))
	{
		// printf("<%d> sterr\n",g_tool.exterr);
		return(0);
	}
	// printf("<%d> TRUE\n",g_tool.exterr);
	assign(sp);
	printall();
	finalizem(0);
	printall();
	return (1);
}
