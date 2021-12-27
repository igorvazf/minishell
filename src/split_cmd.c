/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 10:09:19 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/27 15:04:13 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dirty_job(t_mini *mini, t_list *list, int i, int start)
{
	char	*str;

	while (mini->input_sanitized[i])
	{
		is_in_quote(mini->input_sanitized[i], mini);
		if (mini->input_sanitized[i] == '|' && mini->is_open_s == 0
			&& mini->is_open_d == 0)
		{
			mini->pipe++;
			str = ft_substr(mini->input_sanitized, start, (i - 1) - start);
			i++;
			start = i;
			push_node(list, str);
			free(str);
		}
		if (mini->input_sanitized[i + 1] == '\0' && mini->is_open_s == 0
			&& mini->is_open_d == 0)
		{
			str = ft_substr(mini->input_sanitized, start, i - start + 1);
			push_node(list, str);
			free(str);
		}
		i++;
	}
}

int	split_cmd(t_mini *mini, t_list *list)
{
	int		i;
	int		start;

	i = 0;
	start = i;
	dirty_job(mini, list, i, start);
	if (mini->is_open_s == 1 || mini->is_open_d == 1)
		return (0);
	return (1);
}
