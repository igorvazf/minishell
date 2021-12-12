/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_destroy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:40:22 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/09 15:41:07 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

	node = (t_node *)malloc(sizeof(t_node));
	node->prev = NULL;
	node->next = NULL;
	node->str = ft_split(str, ' ');
	return (node);
}

/*
** Function that destroy (and free all) a double linked list
*/
void	destroy_list(t_list *list)
{
	t_node	*node;
	t_node	*aux;

	node = list->begin;
	while (node->next != NULL)
	{
		minifree(node->str);
		aux = node;
		node = node->next;
		free(aux);
	}
	free(list);
	list = NULL;
}
