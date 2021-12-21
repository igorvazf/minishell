/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 21:32:01 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/20 21:33:26 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_node(char **str)
{
	int	i;
	int len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i][0] == '<' || (str[i][0] == '>'))
			i += 2;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

void	get_cmd(t_node *node)
{
	char	**aux;
	int		i;
	int		len;
	int		j;

	i = 0;
	len = len_node(node->str);
	aux = malloc (sizeof(char *) * len + 1);
	j = 0;
	while (node->str[i])
	{
		if (node->str[i][0] == '<' || (node->str[i][0] == '>'))
			i += 2;
		else
			aux[j++] = ft_strdup(node->str[i++]);
	}
	aux[j] = NULL;
	minifree(node->str);
	node->str = aux;
}
