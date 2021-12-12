/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:58:10 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/12 16:41:57 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		dup_delim(t_mini *mini, int i, int j)
{
	int	k;

	k = 0;
	if (mini->input_sanitized[i] == '>')
	{
		if (mini->input_sanitized[i + 1] == '>')
		{
			mini->io[j] = ft_strdup(">>");
			k++;
		}
		else
			mini->io[j] = ft_strdup(">");
	}
	if (mini->input_sanitized[i] == '<')
	{
		if (mini->input_sanitized[i + 1] == '<')
		{
			mini->io[j] = ft_strdup("<<");
			k++;
		}
		else
			mini->io[j] = ft_strdup("<");
	}
	return (k);
}

void	copy_delim(t_mini *mini)
{
	char	*str;
	int		i;
	int		j;

	str = mini->input_sanitized;
	i = 0;
	j = 0;
	while (str[i])
	{
		is_in_quote(str[i], mini);
		if (str[i] == '|' && mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->io[j] = ft_strdup("|");
		if ((str[i] == '>') && mini->is_open_d == 0 && mini->is_open_s == 0)
			i += dup_delim(mini, i, j);
		if ((str[i] == '<') && mini->is_open_d == 0 && mini->is_open_s == 0)
			i += dup_delim(mini, i, j);
		i++;
		j++;
	}
	mini->io[j] = NULL;
}

void	get_redir(t_mini *mini)
{
	char	*str;
	int		i;
	int		count;

	i = 0;
	count = 0;
	str = mini->input_sanitized;
	while (str[i])
	{
		is_in_quote(str[i], mini);
		if (str[i] == '|' && mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->pipe++;
		if (((str[i] == '<') || str[i] == '>' ) && mini->is_open_d == 0
			&&	mini->is_open_s == 0)
			if (str[i + 1] != '<' || str[i + 1] != '>')
				count++;
		i++;
	}
	if ((mini->pipe + count) > 0)
	{
		mini->io = malloc(sizeof(char *) * (mini->pipe + count) + 1);
		if(!mini->io)
			return ;
		copy_delim(mini);
	}
}

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

void	is_ok(t_mini *mini)//  <| >| >>> <<< <> ><
{
	char	*str;
	int	i;

	i = 0;
	str = mini->input_sanitized;
	while (str[i] && mini->is_ok)
	{
		is_in_quote(str[i], mini);
		if (str[i] == '|' && mini->is_open_s == 0 && mini->is_open_d == 0)
		{
			if (str[i + 1] == '<' || str[i + 1] == '>' || str[i] == '|')
				mini->is_ok = 0;
		}
		else if (str[i] == '<' && mini->is_open_s == 0 && mini->is_open_d == 0)
		{
			if (str[i + 1] == '|' || str[i + 1] == '>'
				|| (str[i + 1] == '<' && str[i + 2] == '<'))
				mini->is_ok = 0;
		}
		else if (str[i] == '>' && mini->is_open_s == 0 && mini->is_open_d == 0)
		{
			if (str[i + 1] == '|' || str[i + 1] == '<'
				|| (str[i + 1] == '>' && str[i + 2] == '>'))
				mini->is_ok = 0;
		}
		i++;
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
