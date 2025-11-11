/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:34:00 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/11 21:20:45 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include <stddef.h>

void	parse(char *line, t_exec_context *exec_context)
{
	t_token	*token_lst;

	token_lst = tokenizer(line);
	if (!token_lst)
		return ;
	if ((check_token_sequence(token_lst) == 0)
		|| check_token_sequence(token_lst) == -1
		|| expand_tokens(token_lst, exec_context) == -1)
	{
		tls_delete_list (&token_lst);
		return ;
	}
	build_cmd_lst(token_lst, exec_context);
	tls_delete_list (&token_lst);
}
