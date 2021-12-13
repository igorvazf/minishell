/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniexport.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 23:15:30 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/13 15:09:04 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		ministrcmp(char *s1, char *s2)
{
	int i;

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

void	copy_var(t_list_env *env, char *str)
{
	t_node_env	*aux;
	char		**var;

	var = ft_split(str, '=');
	aux = env->begin;

	while (aux != NULL)
	{
		if (!ministrcmp(aux->key, var[0]))
			aux = aux->next;
		else
		{
			free(aux->content);
			if(var[1])
				aux->content = ft_strdup(var[1]);
			else
				aux->content = ft_strdup("");
			minifree(var);
			return ;
		}
	}
	add_last_env(env, var[0], var[1]);
	minifree(var);
}

void	miniexport(t_list_env *env, t_node *node)
{
	int			j;

	j = 0;
	while (node->str[1][j] != '=' && node->str[1][j])
		j++;
	if (node->str[1][j] != '=' || j <= 0
		|| (!ft_isalpha(node->str[1][0]) && node->str[1][0] != '_'))
	{
		printf("error\n");
		return ;
	}
	copy_var(env, node->str[1]);
}
