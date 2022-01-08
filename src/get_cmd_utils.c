/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/08 18:49:08 by paugusto          #+#    #+#             */
/*   Updated: 2022/01/08 17:32:00 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_node(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || str[i][0] == '>')
			i += 2;
		else
		{
			i++;
			len++;
		}
	}
	return (len + 1);
}

int	is_just_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != D_QUOTE || str[i] != S_QUOTE)
			return (1);
		i++;
	}
	return (0);
}

int	len_quote(char **str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (is_just_quote(str[i]))
			len++;
		i++;
	}
	return (len);
}
