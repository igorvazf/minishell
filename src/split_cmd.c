/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:19 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/19 15:05:13 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
		if (mini->input_sanitized[i] == '|' && mini->is_open_s == 0
			&& mini->is_open_d == 0)
		{
			mini->pipe++;
			end = i - 1;
			str = ft_substr(mini->input_sanitized, start, end - start);
			i++;
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
