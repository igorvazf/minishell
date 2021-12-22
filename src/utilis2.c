/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/22 11:41:16 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_node(char **str)
{
	int	i;
	int len;

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


char	*get_var_name(char *str)
{
	char	*aux;
	int		i;
	int		len;
	int		j;


	i = 0;
	len = 0;
	j = 0;
	if (str[i] == '$')
	{
		i++;
		while(str[i])
		{
			len++;
			i++;
		}
		aux = malloc(sizeof(char) * len + 1);
		i = 1;
		while (str[i])
			aux[j++] = str[i++];
		aux[j] = '\0';
		return (aux);
	}
	return (NULL);
}

void	expand_var(t_mini *mini, t_node *node)
{
	char		*var;
	t_nodenv	*node_env;
	int			i;

	i = 0;
	node_env = mini->env->begin;
	while (node->str[i])
	{
		if (node->str[i][0] == '$')
		{
			var = get_var_name(node->str[i]);
			break;
		}
		i++;
	}
	if (node->str[i] == NULL)
		return ;
	while (node_env != NULL)
	{
		if(!ft_strcmp(node_env->key, var))
			break;
		node_env = node_env->next;
	}
	if(node_env != NULL)
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(node_env->content);
	}
}

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
	expand_var(mini, node);
}
