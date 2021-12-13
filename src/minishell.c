/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:25:44 by igvaz-fe          #+#    #+#             */
/*   Updated: 2021/12/13 15:07:17 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	back_slash(int sig)
{
	(void)sig;
	printf("Quit (core dumped)\n");
}

void signals(int i)
{
	if (i == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
	}
}
int	main(void)
{
	t_mini		mini;
	t_list		*list;

	mini.env = create_list_env();
	init(&mini, __environ);
	while (1)
	{
		list = create_list();
		get_input(&mini);
		if(ft_strlen(mini.input) != 0)
		{
			if(split_cmd(&mini, list))
			{
				execute(&mini, list);
				//print_elements(list);
			}
			free_em_all(&mini, list);
		}
		else
			free(list);
	}
	free_minishell(&mini);
	return (0);
}
