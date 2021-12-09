/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:40:22 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/09 14:42:57 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Function that creates a double linked list
*/
t_list	*create_list(void)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	list->begin = NULL;
	list->end = NULL;
	list->size = 0;
	return (list);
}

/*
** Funcation that creates a node;
*/
t_node	*create_node(char *str)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->prev = NULL;
	node->next = NULL;
	node->str = ft_split(str, ' ');
	return (node);
}

/*
** Function that destroy (and free all) a double linked list
*/
void	destroy_list(t_list **list_ref)
{
	t_list	*list;
	t_node	*node;
	t_node	*aux;
	int		i;

	list = *list_ref;
	node = list->begin;
	i = 0;
	while (node != NULL)
	{
		aux = node;
		node = node->next;
		while (aux->str[i])
		{
			free(aux->str[i]);
			i++;
		}
		free(aux);
	}
	free(list);
	*list_ref = NULL;
}
