/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_prompt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjmari <tjmari@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 12:37:31 by tjmari            #+#    #+#             */
/*   Updated: 2021/02/14 12:39:50 by tjmari           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    ps1(void)
{
    ft_putstr_fd("\033[1;33mminishell$\033[0m ", 1);
}
