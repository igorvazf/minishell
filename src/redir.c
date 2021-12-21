/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugusto <paugusto@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 17:15:00 by paugusto          #+#    #+#             */
/*   Updated: 2021/12/21 15:30:28 by paugusto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirect_out(t_mini *mini, t_node *node, int i)
{
	int		flags;
	char	*file;

	flags = O_WRONLY | O_CREAT;
	if (node->str[i + 1][0] == '>' || node->str[i + 1][0] == '<'
		|| node->str[i + 1][0] == '\0')
		return (0);
	file = ft_strdup(node->str[i + 1]);
	if (!ft_strcmp(node->str[i], ">>"))
	{
		mini->out = open(file, flags | O_APPEND, 0777);
		free(file);
		return (1);
	}
	else if (!ft_strcmp(node->str[i], ">"))
	{
		mini->out = open(file, flags | O_TRUNC, 0777);
		free(file);
		return (1);
	}
	free(file);
	return (0);
}

void	ft_putstrendl_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (s != 0 && fd != 0)
	{
		while (s[i] != '\0')
		{
			write(fd, &s[i], 1);
			i++;
		}
		write(fd, "\n", 1);
	}
}

void	here_doc(char *file, char *eof)
{
	char	*line;
	int		flags;
	int		fd;

	flags = O_RDWR | O_CREAT | O_TRUNC;
	line = ft_strdup("");
	fd = open(file, flags, 0777);
	while (ft_strcmp(line, eof))
	{
		free (line);
		line = readline("> ");
		if(ft_strcmp(line, eof))
			ft_putstrendl_fd(line, fd);
	}
	close(fd);
	free(line);
}


int	redirect_in(t_mini *mini, t_node *node, int i)
{
	char	*file;
	char	*eof;

	if (!ft_strcmp(node->str[i], "<"))
	{
		file = ft_strdup(node->str[i + 1]);
		mini->in = open(file, O_RDONLY, 0777);
		free(file);
		return (1);
	}
	else if (!ft_strcmp(node->str[i], "<<"))
	{
		//mini->in = open(file, O_RDONLY, 0777);
		eof = ft_strdup(node->str[i + 1]);
		file = ft_strdup("temp");
		here_doc(file, eof);
		mini->in = open(file, O_RDONLY, 0777);
		free(eof);
		free(file);
		return (1);
	}
	return (0);
}
