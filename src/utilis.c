/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:58:10 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/25 22:44:40 by paugusto         ###   ########.fr       */
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
		{
			mini->is_open_s = 0;
			mini->final_s = 1;
		}
	}
	if (c == D_QUOTE)
	{
		if (mini->is_open_d == 0 && mini->is_open_s == 0)
			mini->is_open_d = 1;
		else if (mini->is_open_d == 1)
		{
			mini->is_open_d = 0;
			mini->final_d = 1;
		}
	}
}

int	find_path(t_mini *mini, char *cmd)
{
	char	*path;
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (i < 0 && mini->path[j])
	{
		path = ft_strjoin(mini->path[j], cmd);
		i = access(path, F_OK);
		if (i >= 0)
		{
			mini->correct_path = ft_strdup(path);
			free(path);
			return (1);
		}
		free(path);
		j++;
	}
	i = access(cmd, F_OK);
	if (i >= 0)
	{
		mini->correct_path = ft_strdup(cmd);
		return (1);
	}
	if (ft_strlen(cmd) > 0)
		printf("error command not found\n");
	return (0);
}

int	ministrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		if (s1[i] == s2[i])
			i++;
		else
			return (0);
	}
	if (s1[i] != '\0')
		return (0);
	return (1);
}

int	is_redirect(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}
