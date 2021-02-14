/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:33:25 by tjmari            #+#    #+#             */
/*   Updated: 2021/02/14 12:48:23 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		main(int argc, char *argv[], char *envp[])
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	while (1)
	{
		ps1();
		get_next_line(0, &input);
		if (ft_strncmp(input, "exit\0", 5) == 0)
		{
			free(input);
			break;
		}
		ft_putendl_fd(input, 1);
		// parsing();
		// executing();
		free(input);
	}
	return (0);
}
