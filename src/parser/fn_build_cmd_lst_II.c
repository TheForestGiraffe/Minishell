/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst_II.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/11 23:02:21 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdio.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	*get_heredoc_filename(void)
{
	char				*filename;
	char				*tmp;
	static unsigned int	i = 1;

	while (1)
	{
		tmp = ft_itoa(i);
		if (!tmp)
			return (NULL);
		filename = ft_strjoin(".heredoc_tmp_", tmp);
		free(tmp);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) != 0)
			break ;
		else
		{
			free(filename);
			i++;
		}
	}
	i++;
	return (filename);
}

static int	check_and_expand_line(char **line, t_token_type type,
		t_exec_context *exec_context)
{
	int	ret;

	if (type == WORD)
	{
		ret = expand_vars(line, exec_context);
		if (ret == 0 || ret == -1)
			return (-1);
	}
	return (1);
}

static int	read_and_write_line(t_token *tok, int fd,
		t_exec_context *exec_context)
{
	char	*line;

	line = readline("> ");
	if (!line)
	{
		ft_printf("warning: heredoc ended by end-of-file, wanted 'eof'\n");
		return (1);
	}
	if (ft_strncmp(line, tok->content, ft_strlen(tok->content) + 1) == 0)
	{
		free(line);
		return (1);
	}
	if (check_and_expand_line(&line, tok->type, exec_context) == -1)
	{
		free(line);
		return (-1);
	}
	ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

static int	execute_heredoc(char *filename, t_token *tok,
		t_exec_context *exec_context)
{
	int	fd;
	int	ret;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	while (1)
	{
		ret = read_and_write_line(tok, fd, exec_context);
		if (ret == -1)
		{
			close(fd);
			return (-1);
		}
		if (ret == 1)
			break ;
	}
	close(fd);
	return (1);
}

int	handle_heredoc(t_token *token, t_cmd *cmd, t_exec_context *exec_context)
{
	if (!token || !token->next || !token->next->content || !exec_context)
		return (-1);
	cmd->is_infile_heredoc = true;
	if (!cmd->infile)
		cmd->infile = get_heredoc_filename();
	if (!cmd->infile)
		return (-1);
	if (execute_heredoc(cmd->infile, token->next, exec_context) == -1)
		return (-1);
	return (1);
}
