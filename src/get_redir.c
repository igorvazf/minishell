/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:40:55 by coder             #+#    #+#             */
/*   Updated: 2021/12/14 17:52:27 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		dup_delim(t_mini *mini, int i, int j)
{
	int	k;

	k = 0;
	if (mini->input_sanitized[i] == '>')
	{
		if (mini->input_sanitized[i + 1] == '>' && mini)
		{
			mini->io[j] = ft_strdup(">>");
			k++;
			mini->redir++;
		}
		else
		{
			mini->io[j] = ft_strdup(">");
			mini->redir++;
		}
	}
	if (mini->input_sanitized[i] == '<')
	{
		if (mini->input_sanitized[i + 1] == '<' || mini->input_sanitized[i - 1] == '<')
			k++;
		else
		{
			mini->io[j] = ft_strdup("<");
			mini->redir++;
		}
	}
	return (k);
}

void	copy_delim(t_mini *mini, int count)
{
	char	*str;
	int		i;
	int		j;
	
	mini->io = malloc(sizeof(char *) * count + 1);
	if(!mini->io)
		return ;
	str = mini->input_sanitized;
	i = 0;
	j = 0;
	while (str[i])
	{
		is_in_quote(str[i], mini);
		if (str[i] == '|' && mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->io[j] = ft_strdup("|");
		else if ((str[i] == '>') && mini->is_open_d == 0 && mini->is_open_s == 0)
			i += dup_delim(mini, i, j);
		else if ((str[i] == '<') && mini->is_open_d == 0 && mini->is_open_s == 0)
			i += dup_delim(mini, i, j);
		i++;
		j++;
	}
	mini->io[j] = NULL;
}

void	get_redir(t_mini *mini)
{
	char	*str;
	int		count;
	int		i;

	i = 0;
	count = 0;
	str = mini->input_sanitized;
	while (str[i])
	{
		is_in_quote(str[i], mini);
		if (str[i] == '|' && mini->is_open_d == 0 && mini->is_open_s == 0)
		{
			mini->pipe++;
			count++;
		}
		if (str[i] == '<' && (i = 0 || str[i - 1] != '<') && str[i + 1] != '<')
		{
			mini->redir++;
			count++;
		}
		if (str[i] == '>')
			if (str[i + 1] != '>')
			{
				count++;
				mini->redir++;
			}
		i++;
	}
	if (count > 0)
		copy_delim(mini, count);
}