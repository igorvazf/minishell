/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:19 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/17 00:30:29 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_delim(t_mini *mini, int i)
{
	if(mini->input_sanitized[i] == '|')
	{
		mini->pipe++;
		return (1);
	}
	else if (mini->input_sanitized[i] == '<')
		return (1);
	else if(mini->input_sanitized[i] == '>')
		return (1);
	return (0);
}	


int	split_cmd(t_mini *mini, t_list *list)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	start = i;
	end = i;
	while (mini->input_sanitized[i])
	{
		is_in_quote(mini->input_sanitized[i], mini);
		if (is_delim(mini, i) && mini->is_open_s == 0
			&& mini->is_open_d == 0)
		{
			end = i - 1;
			str = ft_substr(mini->input_sanitized, start, end - start);
			start = i;
			while (mini->input_sanitized[i] && (is_delim(mini, i) || mini->input_sanitized[i] == ' '))
				i++;
			push_node(list, str);
			free(str);
		}
		if (mini->input_sanitized[i + 1] == '\0' && mini->is_open_s == 0
			&& mini->is_open_d == 0)
		{
			end = i;
			str = ft_substr(mini->input_sanitized, start, end - start + 1);
			push_node(list, str);
			free(str);
		}
		i++;
	}
	return (1);
}
