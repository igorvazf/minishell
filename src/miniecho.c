/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:45:50 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/27 15:17:36 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print(t_mini *mini, t_node *node, int i, int j)
{
	while (node->str[i][j])
	{
		is_in_quote(node->str[i][j], mini);
		if (mini->is_open_s == 1 || mini->final_s == 1)
		{
			if (node->str[i][j] != S_QUOTE)
				printf("%c", node->str[i][j]);
		}
		if (mini->is_open_d == 1 || mini->final_d == 1)
		{
			if (node->str[i][j] != D_QUOTE)
				printf("%c", node->str[i][j]);
		}
		if (mini->is_open_s == 0 && mini->is_open_d == 0
			&& mini->final_s == 0 && mini->final_d == 0)
			printf("%c", node->str[i][j]);
		else if (mini->final_s == 1 || mini->final_d == 1)
		{
			mini->final_s = 0;
			mini->final_d = 0;
		}
		j++;
	}
}

void	miniecho(t_mini *mini, t_node *node)
{
	int	i;

	i = 1;
	mini->final_d = 0;
	mini->final_s = 0;
	if (node->str[1] && !ft_strncmp(node->str[1], "-n\0", 3))
		i++;
	if (node->str[i])
	{
		while (node->str[i] && node->str[i][0] != '<' && node->str[i][0] != '>')
		{
			print(mini, node, i, 0);
			if (node->str[i + 1] != NULL)
				printf(" ");
			i++;
		}
		if (ft_strncmp(node->str[1], "-n\0", 3))
			printf("\n");
	}
}
