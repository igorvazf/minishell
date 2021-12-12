/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:40:22 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/12 16:36:18 by paugusto         ###   ########.fr       */
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
	node->next = NULL;
	node->str = ft_split(str, ' ');
	return (node);
}

/*
** Function that adds an element at the end of the list
*/
void	add_last(t_list *list, char *str)
{
	t_node	*node;

	node = create_node(str);
	if (list->size == 0)
		list->begin = node;
	else
		list->end->next = node;
	list->end = node;
	list->size++;
}
