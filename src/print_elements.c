/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:46:20 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/09 15:41:10 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** Function that prints every element in a list
*/
void	print_elements(t_list *list)
{
	t_node	*node;
	int		i;

	node = list->begin;
	while (node != NULL)
	{
		for(i = 0; node->str[i]; i++)
			printf("%s -> ", node->str[i]);
		node = node->next;
	}
	printf("NULL\n");
	if (list->end == NULL)
		printf("list->end == NULL\n");
	else
		printf("list->end == %s\n", list->end->str[i]);
	printf("size: %lu\n", list->size);
	puts("");
}

/*
** Function that prints every element in a list from the end to the beginning
*/
void	print_inverted_elements(t_list *list)
{
	t_node	*node;
	int		i;

	node = list->end;
	while (node != NULL)
	{
		for(i = 0; node->str[i]; i++)
			printf("%s -> ", node->str[i]);
		node = node->prev;
	}
	printf("NULL\n");
	if (list->end == NULL)
		printf("list->begin == NULL\n");
	else
		printf("list->begin == %s\n", list->begin->str[i]);
	printf("size: %lu\n", list->size);
	puts("");
}
