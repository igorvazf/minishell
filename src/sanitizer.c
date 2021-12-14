/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: coder <coder@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 10:41:53 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/14 01:39:08 by coder            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*put_spaces(char *str, int len)
{
	char	*input;
	int		i;
	int		j;

	input = malloc(sizeof(char) * len + 1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != ' '
			&& (str[i + 1]  == '|' || (str[i + 1] == '>' && str[i] != '>')|| (str[i + 1] == '<' && str[i - 1] != '<' && str[i] != '<')))
		{
			input[j++] = str[i++];
			input[j++] = ' ';
		}
		else if ((str[i] == '>' && str[i + 1] == '>'))
		{
			input[j++] = str[i++];
			input[j++] = str[i++];
			input[j++] = ' ';
		}
		else if ((str[i]  == '|' || str[i] == '>' || (str[i + 1] == '<' && str[i - 1] != '<' && str[i] != '<'))
				&& (str[i + 1] != ' ' && str[i + 1] != '\0'))
		{
			input[j++] = str[i++];
			input[j++] = ' ';
		}
		else
			input[j++] = str[i++];
	}
	input[j] = '\0';
	return (input);
}

int	correct_len(char	*str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i]) 
	{
		if (str[i] != ' '
			&& (str[i + 1]  == '|' || (str[i + 1] == '>' && str[i] != '>')
			|| (str[i + 1] == '<' && str[i - 1] != '<' && str[i] != '<')))
		{
			len = len + 2;
			i++;
		}
		else if ((str[i]  == '|' || (str[i] == '>' && str[i + 1] == '>') || (str[i + 1] == '<' && str[i - 1] != '<' && str[i] != '<'))
				&& (str[i + 1] != ' ' && str[i + 1] != '\0'))
		{
			len = len + 2;
			i++;
		}
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

void	input_sanitizer(t_mini *mini)
{
	char	*aux;
	int		len;

	aux = ft_strtrim(mini->input, " ");
	len = correct_len(aux);
	mini->input_sanitized = put_spaces(aux, len);
	free(aux);
}
