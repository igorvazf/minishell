/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:45:50 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/07 17:26:34 by paugusto         ###   ########.fr       */
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
				ft_putchar_fd(node->str[i][j], mini->out);
		}
		if (mini->is_open_d == 1 || mini->final_d == 1)
		{
			if (node->str[i][j] != D_QUOTE)
				ft_putchar_fd(node->str[i][j], mini->out);
		}
		if (mini->is_open_s == 0 && mini->is_open_d == 0
			&& mini->final_s == 0 && mini->final_d == 0)
			ft_putchar_fd(node->str[i][j], mini->out);
		else if (mini->final_s == 1 || mini->final_d == 1)
		{
			mini->final_s = 0;
			mini->final_d = 0;
		}
		j++;
	}
}

void	is_in_quote_str(char *str, t_mini *mini)
{
	if (str[0] == S_QUOTE && str[1] == '\0')
	{
		if (mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
			mini->is_open_s_str = 1;
		else if (mini->is_open_s_str == 1)
			mini->is_open_s_str = 0;
	}
	if (str[0] == D_QUOTE && str[1] == '\0')
	{
		if (mini->is_open_d_str == 0 && mini->is_open_s_str == 0)
			mini->is_open_d_str = 1;
		else if (mini->is_open_d_str == 1)
			mini->is_open_d_str = 0;
	}
}

void	miniecho(t_mini *mini, t_node *node)
{
	int	i;

	i = 1;
	mini->final_d = 0;
	mini->final_s = 0;
	mini->is_open_s_str = 0;
	mini->is_open_d_str = 0;
	while (node->str[i] && !ft_strcmp(node->str[i], "-n"))
		i++;
	if (node->str[i])
	{
		while (node->str[i])
		{
			is_in_quote_str(node->str[i], mini);
			if ((node->str[i][0] == '>' || node->str[i][0] == '<')
				&& mini->is_open_s_str == 0 && mini->is_open_d_str == 0)
				break;
			print(mini, node, i, 0);
			if (node->str[i + 1] != NULL)
				ft_putchar_fd(' ', mini->out);
			i++;
		}
		if (ft_strncmp(node->str[1], "-n\0", 3))
			ft_putchar_fd('\n', mini->out);
	}
}
