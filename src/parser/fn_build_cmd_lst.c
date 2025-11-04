/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/03 12:13:45 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

static int	convert_token(t_token **token, t_cmd **cmd, t_cmd **cmd_lst);
static int	handle_redirection(t_token *cmd, t_cmd *token);
static int	handle_out_and_rout(t_token *token, t_cmd *cmd);
static int	handle_heredoc(t_token *token, t_cmd *cmd);

t_cmd	*build_cmd_lst(t_token *token_lst)
{
	t_cmd	*cmd_lst;
	t_cmd	*cmd;
	t_token	*token;

	if (!token_lst)
		return (NULL);
	token = token_lst;
	cmd_lst = NULL;
	cmd = cmd_lst_create();
	if (!cmd)
		return (NULL);
	if (cmd_lst_add_back(&cmd_lst, cmd) == -1)
		return (NULL);
	while (token)
	{
		if (convert_token(&token, &cmd, &cmd_lst) == -1)
		{
			cmd_lst_delete_list(&cmd_lst);
			return (NULL);
		}
		token = token->next;
	}
	return (cmd_lst);
}

static int	convert_token(t_token **token, t_cmd **cmd, t_cmd **cmd_lst)
{
	if (((*token)->type == WORD) || ((*token)->type == S_QT)
		|| ((*token)->type == D_QT))
	{
		if (add_argv(*token, *cmd) == -1)
			return (-1);
	}
	else if ((*token)->type == PIPE)
	{
		*cmd = cmd_lst_create();
		if (!*cmd || (cmd_lst_add_back(cmd_lst, *cmd) == -1))
			return (-1);
	}
	else if (((*token)->type == INPUT) || ((*token)->type == OUTPUT)
		|| ((*token)->type == RINPUT) || ((*token)->type == ROUTPUT))
	{
		if (handle_redirection(*token, *cmd) == -1)
			return (-1);
		*token = (*token)->next;
	}
	return (1);
}

int	handle_redirection(t_token *token, t_cmd *cmd)
{
	if (token->type == INPUT)
	{
		free(cmd->infile);
		cmd->infile = ft_strdup(token->next->content);
		if (!cmd->infile)
			return (-1);
	}
	else if (token->type == OUTPUT || token->type == ROUTPUT)
	{
		if (handle_out_and_rout(token, cmd) == -1)
			return (-1);
	}
	else if (token->type == RINPUT)
	{
		if (handle_heredoc(token, cmd) == -1)
			return (-1);
	}
	return (1);
}

static int	handle_out_and_rout(t_token *token, t_cmd *cmd)
{
	int	fd;

	free(cmd->outfile);
	cmd->outfile = ft_strdup(token->next->content);
	if (!cmd->outfile)
		return (-1);
	if (token->type == OUTPUT)
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
	{
		fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		cmd->append = true;
	}
	if (fd == -1)
	{
		ft_putstr_fd("@handle_redirection: could not create file", 2);
		return (-1);
	}
	close(fd);
	return (1);
}

static int	handle_heredoc(t_token *token, t_cmd *cmd)
{
	if (!token || !token->next || !token->next->content || !cmd)
		return (-1);
	cmd->is_infile_heredoc = true;
	free(cmd->infile);
	cmd->infile = ft_strdup(token->next->content);
	if (!cmd->infile)
		return (-1);
	return (1);
}
