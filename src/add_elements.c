/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_elements.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:43:32 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/09 15:41:02 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Function that check if the list is empty
*/
bool	is_list_empty(const t_list *list)
{
	return (list->size == 0);
}

/*
** Function that adds an element at the beginning of the list
*/
void	add_first(t_list *list, char *str)
{
	t_node	*node;

	node = create_node(str);
	node->next = list->begin;
	if(is_list_empty(list))
		list->end = node;
	else
		list->begin->prev = node;
	list->begin = node;
	list->size++;
}

/*
** Function that adds an element at the end of the list
*/
void	add_last(t_list *list, char *str)
{
	t_node	*node;

	node = create_node(str);
	node->prev = list->end;
	if (is_list_empty(list))
		list->begin = node;
	else
		list->end->next = node;
	list->end = node;
	list->size++;
}
