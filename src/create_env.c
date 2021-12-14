/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 19:40:27 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 15:08:54 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Function that creates a linked list
*/
t_list_env	*create_list_env(void)
{
	t_list_env	*list;

	list = malloc(sizeof(t_list_env));
	list->begin = NULL;
	list->end = NULL;
	list->size = 0;
	return (list);
}

/*
** Funcation that creates a node;
*/
t_node_env	*create_node_env(char *key, char *content)
{
	t_node_env	*node;

	node = (t_node_env *)malloc(sizeof(t_node_env));
	node->next = NULL;
	node->key = ft_strdup(key);
	if (content)
		node->content = ft_strdup(content);
	else
		node->content = ft_strdup("");
	return (node);
}

/*
** Function that adds an element at the end of the list
*/
void	add_last_env(t_list_env *list, char *key, char *content)
{
	t_node_env	*node;

	node = create_node_env(key, content);
	if (list->size == 0)
		list->begin = node;
	else
		list->end->next = node;
	list->end = node;
	list->size++;
}
