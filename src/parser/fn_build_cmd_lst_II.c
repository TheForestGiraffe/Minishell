/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst_II.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/07 15:19:55 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <readline/readline.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

static int	execute_heredoc(char *filename, t_token *delim_token, char **envp);
static int	check_and_expand_line(char **line, t_token_type type, char **envp);
static int	read_and_write_line(t_token *tok, int fd, char **envp);
static char	*get_heredoc_filename(void);

int	handle_heredoc(t_token *token, t_cmd *cmd, char **envp)
{
	if (!token || !token->next || !token->next->content || !cmd)
		return (-1);
	cmd->is_infile_heredoc = true;
	if (!cmd->infile)
		cmd->infile = get_heredoc_filename();
	if (!cmd->infile)
		return (-1);
	if (execute_heredoc(cmd->infile, token->next, envp) == -1)
		return (-1);
	return (1);
}

static int	execute_heredoc(char *filename, t_token *tok, char **envp)
{
	int	fd;
	int	ret;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);
	while (1)
	{
		ret = read_and_write_line(tok, fd, envp);
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

static int	read_and_write_line(t_token *tok, int fd, char **envp)
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
	if (check_and_expand_line(&line, tok->type, envp) == -1)
	{
		free(line);
		return (-1);
	}
	ft_putendl_fd(line, fd);
	free(line);
	return (0);
}

static int	check_and_expand_line(char **line, t_token_type type, char **envp)
{
	int	ret;

	if (type == WORD)
	{
		ret = expand_vars(line, envp);
		if (ret == 0 || ret == -1)
			return (-1);
	}
	return (1);
}

static char	*get_heredoc_filename(void)
{
	char				*filename;
	static unsigned int	i = 1;

	while (1)
	{
		filename = ft_strjoin(".heredoc_tmp_", ft_itoa(i));
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
