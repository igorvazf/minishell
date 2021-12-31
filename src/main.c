/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/31 12:23:41 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;
int	g_return;

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

int	main(void)
{
	t_mini	mini;
	t_list	*list;
	t_sani	sani;

	init(&mini, environ);
	while (1)
	{
		signals(1);
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini, &sani);
		if (ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{
			if (!ft_strcmp(mini.input, "exit"))
				miniexit(&mini, list);
			if (split_cmd(&mini, list) && validade(list))
			{
				//print_elements(list);
				run(&mini, list);
			}
		}
		free_reset(&mini, list);
		mini.pipe = 0;
	}
	free_em_all(&mini);
	return (0);
}
