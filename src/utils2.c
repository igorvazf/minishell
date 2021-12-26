/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/25 22:45:41 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

char	*get_var_content(t_mini *mini, char *key)
{
	t_nodenv	*node_env;

	node_env = mini->env->begin;
	while (node_env != NULL)
	{
		if (!ft_strcmp(node_env->key, key))
			return (ft_strdup(node_env->content));
		node_env = node_env->next;
	}
	return (NULL);
}

char	*get_var(t_mini *mini, char *str, int i)
{
	char	*var;
	char	*content;
	int		len;
	int		j;

	len = 0;
	j = i;
	while (str[i] && str[i] != '$')
	{
		len++;
		i++;
	}
	if (len > 0)
	{
		var = malloc (sizeof(char) * len + 1);
		i = 0;
		while (str[j] && str[j] != '$' && str[j] != D_QUOTE)
			var[i++] = str[j++];
		content = get_var_content(mini, var);
		free(var);
		return (content);
	}
	return (NULL);
}

char	*get_join(char *str)
{
	int		i;
	char	*aux;

	i = 0;
	if (str[i] == '$')
		return (NULL);
	while (str[i] && str[i] != '$')
		i++;
	aux = ft_substr(str, 0, i - 1);
	return (aux);
}

void	expand_var(t_mini *mini, t_node *node, int i)
{
	char		*content;
	char		*holder;
	char		*aux;
	int			j;

	j = 0;
	content = NULL;
	holder = get_join(node->str[i]);
	while (node->str[i][j])
	{
		if (node->str[i][j] == '$')
		{
			content = get_var(mini, node->str[i], j + 1);
			if (content != NULL)
			{
				aux = holder;
				if (holder == NULL)
					aux = ft_strdup("");
				holder = ft_strjoin(aux, content);
				free(aux);
				free(content);
			}
		}
		j++;
	}
	if (holder != NULL)
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(holder);
		free(holder);
	}
	else
	{
		free(node->str[i]);
		node->str[i] = ft_strdup(" ");
	}
}

void check_dollar(t_mini *mini, t_node *node)
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
				break;
			}
			j++;
		}
		i++;
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
	check_dollar(mini, node);
}
