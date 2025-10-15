/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_sequence.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:17:15 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/12 18:52:44 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "local_parser.h"

static int	check_pipe(t_token *curr_token, t_token *token_lst);
static int	is_redirection(t_token_type type);
static int	check_redirection(t_token *token);

int	check_token_sequence(t_token *token_lst)
{
	t_token	*curr_token;

	if (!token_lst)
		return (-1);
	curr_token = token_lst;
	while (curr_token)
	{
		if (curr_token->type == PIPE)
		{
			if (check_pipe(curr_token, token_lst) == 0)
				return (0);
		}
		else if (is_redirection(curr_token->type))
		{
			if (check_redirection(curr_token) == 0)
				return (0);
		}
		curr_token = curr_token->next;
	}
	return (1);
}

static int	check_pipe(t_token *curr_token, t_token *token_lst)
{
	if ((curr_token == token_lst) && (curr_token->type == PIPE))
	{
		ft_putstr_fd("minishell: syntax error near token '|'\n", 2);
		return (0);
	}
	if ((curr_token->type == PIPE) && (curr_token->next))
	{
		if (curr_token->next->type == PIPE)
		{
			ft_putstr_fd("minishel: syntax error near token '|'\n", 2);
			return (0);
		}
	}
	if ((curr_token->type == PIPE) && (!curr_token->next))
	{
		ft_putstr_fd("minishel: syntax error near token '|'\n", 2);
		return (0);
	}
	return (1);
}

static int	is_redirection(t_token_type type)
{
	if (type == INPUT || type == OUTPUT || type == RINPUT || type == ROUTPUT)
		return (1);
	return (0);
}

static int	check_redirection(t_token *token)
{
	if (!token->next)
	{
		ft_putstr_fd("minishel: syntax error near token '", 2);
		ft_putstr_fd(token->content, 2);
		ft_putstr_fd("'\n", 2);
		return (0);
	}
	if ((token->next->type == WORD) || (token->next->type == S_QT)
		|| (token->next->type == D_QT))
		return (1);
	ft_putstr_fd("minishel: syntax error near token '", 2);
	ft_putstr_fd(token->content, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}
