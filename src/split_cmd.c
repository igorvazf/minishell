/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:19 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/15 03:22:59 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_delim(t_mini *mini, int i)
{
	if(mini->input_sanitized[i] == '|')
		return (1);
	else if (mini->input_sanitized[i] == '<')
	{
		if (mini->input_sanitized[i + 1] != '<' && mini->input_sanitized[i - 1] != '<')
			return (1);
	}
	else if(mini->input_sanitized[i] == '>')
		return (1);
	return (0);
}	

int	validate(t_mini *mini, int i)
{
	char	*str;
	str = mini->input_sanitized;
	if (str[i] == '>')
	{
		if(i == 0)
			mini->init_with_arrow = 1;
		if (str[i + 1] == '>')
			return (i + 2);
		else
			return (i + 1);
	}
	else if (str[i] == '<' && str[i + 1] != '<' && str[i - 1] != '<')
	{
		if(i == 0)
			mini->init_with_arrow = 1;
		return (i + 1);
	}
	else if (str[i] == '|')
		return (i + 1);
	else
		return (i);
}

int	split_cmd(t_mini *mini, t_list *list)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	if (mini->input_sanitized[i] == '|')
		return (0);
	i = validate(mini, i);
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
			i = validate(mini, i);
			start = i;
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
