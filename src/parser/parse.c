/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:00 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/03 12:37:05 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

//TODO: Remove after implementing build cmd_list

t_cmd	*parse(char *line, char **envp)
{
	t_token	*token_lst;
	t_cmd	*cmd_lst;

	token_lst = tokenizer(line);
	if (!token_lst)
		return (NULL);
	if ((check_token_sequence(token_lst) == 0)
		|| check_token_sequence(token_lst) == -1)
		return (NULL);
	expand_tokens(token_lst, envp);
	cmd_lst = build_cmd_lst(token_lst);
	return (cmd_lst);
}
