/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:58:10 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/06 11:58:14 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_quotes_closed(t_mini *mini)
{
	char	*str;
	int		i;

	str = mini->input_sanitized;
	i = 0;
	while(str[i])
	{
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			if (mini->is_open == 0)
				mini->is_open = 1;
			else if (mini->is_open == 1)
				mini->is_open = 0;
		}
		i++;
	}
	if (mini->is_open == 1)
	{
		printf("erro, nao fechou aspas\n");
		mini->is_open = 0;
	}
}
