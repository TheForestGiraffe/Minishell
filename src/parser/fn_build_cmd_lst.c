/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/17 14:03:31 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

static int	handle_redirection(t_cmd *cur_cmd, t_cmd *cur_token);

t_cmd	*build_cmd_lst(t_token *token_lst)
{
	t_cmd	*cmd_lst;
	t_cmd	*cur_cmd;
	t_token	*cur_token;

	if (!token_lst)
		return (NULL);
	cur_token = token_lst;
	cmd_lst = NULL;
	cur_cmd = cmd_lst_create();
	if (!cur_cmd)
		return (NULL);
	if (cmd_lst_add_back(&cmd_lst, cur_cmd) == -1)
		return (NULL);
	while (cur_token)
	{
		if ((cur_token->type == WORD) || (cur_token->type == S_QT) || 
			(cur_token->type == D_QT))
		{
			if (add_argv(cur_token, cur_cmd) == -1)
			{
				cmd_lst_delete_list(&cmd_lst);
				return (NULL);
			}
		}
		else if (cur_token->type == PIPE)
		{
			cur_cmd = cmd_lst_create();
			if (!cur_cmd || (cmd_lst_add_back(&cmd_lst, cur_cmd) == -1))
			{
				cmd_lst_delete_list(&cmd_lst);
				return (NULL);
			}
		}
		else if ((cur_token->type == INPUT) || (cur_token->type == OUTPUT)
			|| (cur_token->type == RINPUT) || (cur_token->type == ROUTPUT))
		{
			handle_redirection(cur_cmd, cur_token);
		}
		cur_token = cur_token->next;
	}
	return (cmd_lst);
}

int	handle_redirection(t_cmd *cur_cmd, t_cmd *cur_token)
{
	if (cur_token->)
	return (1);
}
