/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 22:10:51 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/31 12:29:52 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int signum)
{
	if (signum == SIGINT)
	{
		g_return = 130;
		write(1, "\n", 1);
	}
	if (signum == SIGQUIT)
	{
		g_return = 131;
		write(1, "\n", 1);
		printf("Quit (core dumped)\n");
	}
}

void	handler_main(int signum)
{
	(void)signum;
	g_return = 130;
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	// rl_on_new_line();
	// rl_redisplay();e
}

void signals(int signum)
{
	if (signum == 1) //main.c
	{
		signal(SIGINT, handler_main);
		signal(SIGQUIT, SIG_IGN);
	}
	if (signum == 2) //exec.c
	{
		signal(SIGINT, handler);
		signal(SIGQUIT, handler);
	}
}
