/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/25 22:20:20 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/31 20:57:25 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
** function that check sequences of '<' and '>'
*/
int	check_validate(char	*str)
{
	int	i;
	int	count;

	i = 0;
	while (str[i])
	{
		count = 0;
		while (str[i] == '<' || str[i] == '>')
		{
			i++;
			count++;
		}
		if (count >= 3)
			return (0);
		i++;
	}
	return (1);
}

int	validade(t_list *list)
{
	t_node	*node;
	int		i;

	node = list->begin;
	i = 0;
	while (node != NULL)
	{
		while (node->str[i])
		{
			if (!check_validate(node->str[i]))
			{
				printf("error\n");
				return (0);
			}
			i++;
		}
		node = node->next;
	}
	return (1);
}

/*
** function that takes input from user and add to the history
*/
void	get_input(t_mini *mini, t_sani *sani)
{
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->input = readline(">> ");
	if (mini->input)
	{
		if (ft_strlen(mini->input) != 0)
			add_history(mini->input);
		input_sanitizer(mini, sani);
	}
	else
		printf("\n");
}
