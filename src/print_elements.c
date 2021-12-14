/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:46:20 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 01:07:37 by coder            ###   ########.fr       */
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
			printf("%s .. ", node->str[i]);
		printf("\n");
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

void	print_env(t_list_env *list)
{
	t_node_env	*node;

	node = list->begin;
	while (node->next != NULL)
	{
		printf("%s=%s\n", node->key, node->content);
		node = node->next;
	}
	printf("%s=%s\n", node->key, node->content);
}
