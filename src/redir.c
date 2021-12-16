/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 15:40:55 by coder             #+#    #+#             */
/*   Updated: 2021/12/16 15:53:10 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	dup_delim(t_mini *mini, int i, int j)
{
	int	k;
	
	k = 0;
	if (mini->input_sanitized[i] == '>')
	{
		if (mini->input_sanitized[i + 1] == '>' && mini)
		{
			mini->io[j] = ft_strdup(">>");
			mini->redir++;
			k++;
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

void	copy_delim(t_mini *mini)
{
	char	*str;
	int		i;
	int		j;

	mini->io = malloc(sizeof(char *) * (mini->pipe + mini->redir) + 1);
	if (!mini->io)
		return ;
	mini->pipe = 0;
	mini->redir = 0;
	str = mini->input_sanitized;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '|')
		{
			mini->io[j] = ft_strdup("|");
			mini->pipe++;
			j++;
		}
		else if (str[i] == '>')
		{
			i += dup_delim(mini, i, j);
			j++;
		}
		else if (str[i] == '<')
		{
			i += dup_delim(mini, i, j);
			j++;
		}
		i++;
	}
	mini->io[j] = NULL;
}

void	get_redir(t_mini *mini)
{
	char	*str;
	int		i;

	str = mini->input_sanitized;
	i = 0;
	while (str[i])
	{
		if (str[i] == '|')
			mini->pipe++;
		else if (str[i] == '>')
		{
			if (mini->input_sanitized[i + 1] == '>' && mini)
			{
				i++;
				mini->redir++;
			}
			else
				mini->redir++;
		}
		else if (str[i] == '<')
		{
			if (mini->input_sanitized[i + 1] == '<')
				i++;
			else
				mini->redir++;
		}
		i++;
	}
	if (mini->pipe + mini->redir > 0)
		copy_delim(mini);
}