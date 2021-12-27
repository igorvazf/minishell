/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/27 14:34:11 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** function that expands variables if it exist
*/
void	check_dollar(t_mini *mini, t_node *node)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (node->str[i])
	{
		j = 0;
		while (node->str[i][j])
		{
			is_in_quote(node->str[i][j], mini);
			if (mini->is_open_s == 0 && node->str[i][j] == '$')
			{
				expand_var(mini, node, i);
				break ;
			}
			j++;
		}
		i++;
	}
}

int	len_node(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || (str[i][0] == '>'))
			i += 2;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

/*
** function that prepares the right command and cleans it
*/
void	get_cmd(t_mini *mini, t_node *node)
{
	char	**aux;
	int		i;
	int		len;
	int		j;

	i = 0;
	len = len_node(node->str);
	aux = malloc (sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		if (node->str[i][0] == '<' || (node->str[i][0] == '>'))
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	minifree(node->str);
	node->str = aux;
	check_dollar(mini, node);
}
