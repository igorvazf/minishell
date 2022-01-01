/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/01 01:00:58 by paugusto         ###   ########.fr       */
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

char	**removeq(char **str, int len, int i, int k)
{
	char	**aux;
	char	*holder;
	int		j;
	int		start;
	int		end;

	aux = malloc(sizeof(char *) * len + 1);
	while (str[i])
	{
		if (is_just_quote(str[i]))
		{
			j = 0;
			holder = ft_strdup(str[i]);
			while (holder[j] && holder[j] == ' ')
				j++;
			while (holder[j] && (holder[j] == D_QUOTE || holder[j] == S_QUOTE))
				j++;
			start = j;
			while (holder[j] && holder[j] != D_QUOTE && holder[j] != S_QUOTE)
				j++;
			end = j - 1;
			aux[k] = ft_substr(holder, start, end - start + 1);
			k++;
			free(holder);
		}
		i++;
	}
	aux[k] = NULL;
	return (aux);
}

/*
** function that prepares the right command and cleans it
*/
void	get_cmd(t_mini *mini, t_node *node)
{
	char	**aux;
	char	**holder;
	int		i;
	int		j;
	int		len;

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
	len = len_node(aux);
	holder = removeq(aux, len, 0, 0);
	minifree(node->str);
	minifree(aux);
	node->str = holder;
	check_dollar(mini, node);
}

void	get_cmd_builtin(t_mini *mini, t_node *node)
{
	char	**aux;
	int		i;
	int		j;
	int		len;

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
	minifree(node->str);
	node->str = aux;
	check_dollar(mini, node);
}
