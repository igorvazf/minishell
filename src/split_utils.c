/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:58:10 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 15:45:59 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_in_quote(char c, t_mini *mini)
{

	if (c == S_QUOTE)
	{
		if (mini->is_open_s == 0 && mini->is_open_d == 0)
			mini->is_open_s = 1;
		else if (mini->is_open_s == 1)
			mini->is_open_s = 0;
	}
	if (c == D_QUOTE)
	{
		if (mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->is_open_d = 1;
		else if (mini->is_open_d == 1)
			mini->is_open_d = 0;
	}
}

void	is_quotes_closed(t_mini *mini)
{
	int		i;

	i = 0;
	while(mini->input_sanitized[i])
	{
		is_in_quote(mini->input_sanitized[i], mini);
		i++;
	}
}

void	find_path(t_mini *mini, t_list *list)
{
	int	i;
	int	j;
	char	*path;


	i = -1;
	j = 0;
	while (i < 0 && mini->path[j])
	{
		path = ft_strjoin(mini->path[j], list->end->str[0]);
		i = access(path, F_OK);
		if (i >= 0)
			mini->correct_path = ft_strdup(path);
		free(path);
		j++;
	}
	if (i == -1)
	{
		printf("command not found\n");
	}
}
