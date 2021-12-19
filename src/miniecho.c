/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniecho.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:45:50 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/19 18:24:10 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	miniecho(t_node *node)
{
	int i;

	i = 1;
	if (!ft_strncmp(node->str[1], "-n\0", 3))
		i++;
	while (node->str[i] && node->str[i][0] != '<' && node->str[i][0] != '>')
	{
		printf("%s", node->str[i]);
		if (node->str[i + 1] != NULL)
			printf(" ");
		i++;
	}
	if (ft_strncmp(node->str[1], "-n\0", 3))
		printf("\n");
}
