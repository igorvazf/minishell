/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:35:22 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/01 01:33:58 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniexit(t_mini *mini, t_node *node, t_list *list)
{
	int	code;

	code = 0;
	if (node->str[1] && ft_strcmp(node->str[1], "exit"))
		code = ft_atoi(node->str[1]);
	free_reset(mini, list);
	free_em_all(mini);
	exit(code);
}
