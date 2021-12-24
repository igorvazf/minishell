/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/23 21:22:53 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char **environ;

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
				printf("parse error\n");
				return (0);
			}
			i++;

		}
		node = node->next;
	}

	return (1);
}

void	get_input(t_mini *mini, t_sani *sani)
{
	mini->is_open_s = 0;
	mini->is_open_d = 0;
	mini->input = readline(">> ");
	if (ft_strlen(mini->input) != 0)
		add_history(mini->input);
	input_sanitizer(mini, sani);
}

int	main(void)
{
	t_mini	mini;
	t_list	*list;
	t_sani	sani;

	init(&mini, environ);
	//print_env(mini.env);
	while (1)
	{
		mini.in = STDIN_FILENO;
		mini.out = STDOUT_FILENO;
		list = create_list();
		get_input(&mini, &sani);
		//printf("%s\n", mini.input_sanitized);
		if(ft_strlen(mini.input) != 0 && mini.input[0] != '|')
		{
			if (!ft_strcmp(mini.input, "exit"))
				miniexit(&mini, list);
			if(split_cmd(&mini, list) && validade(list))
			{
				run(&mini, list);
			}
		}
		free_reset(&mini, list);
		mini.pipe = 0;
	}
	free_em_all(&mini);
	return (0);
}
