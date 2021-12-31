/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/31 16:33:21 by paugusto         ###   ########.fr       */
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

int	is_just_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != D_QUOTE || str[i] != S_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

int	len_quote(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_just_quote(str[i]))
			len++;
		i++;
	}
	return (len);
}

/*
** function that prepares the right command and cleans it
*/
void	get_cmd(t_mini *mini, t_node *node)
{
	char	**aux;
	char	**holder;
	char	*str;
	int		i;
	int		len;
	int		j;
	int		start;
	int		end;
	int		k;

	i = 0;
	len = len_node(node->str);
	aux = malloc(sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		if (node->str[i][0] == '<' || (node->str[i][0] == '>'))
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	len = len_quote(aux);
	holder = malloc(sizeof(char *) * len + 1);
	i = 0;
	k = 0;
	while (aux[i])
	{
		if (is_just_quote(aux[i]))
		{
			j =  0;
			str = ft_strdup(aux[i]);
			while (str[j] && str[j] == ' ')
				j++;
			while ((str[j] == D_QUOTE || str[j] == S_QUOTE) && str[j])
				j++;
			start = j;
			while (str[j] && str[j] != D_QUOTE)
				j++;
			end = j - 1;
			holder[k] = ft_substr(str, start, end - start + 1);
			free(str);
			k++;
		}
		i++;
	}
	holder[k] = NULL;
	minifree(aux);
	minifree(node->str);
	node->str = holder;
	check_dollar(mini, node);
}
