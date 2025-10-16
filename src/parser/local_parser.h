/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/16 15:57:12 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_PARSER_H
# define LOCAL_PARSER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "parser.h"

// fn_tokenizer.c
t_token	*tokenizer(char *str);

// fn_tocken_lists.c
int		tls_add_back(t_token **lst, t_token *new);
void	tls_delete_list(t_token **head);
t_token	*tls_create(char *str);
int		add_buf_to_list(char *buf, t_token **head, t_token_type type);

// fn_helpers.c
int		fn_is_space(char c);
int		fn_is_res(char c);
void	figure_type(t_token **current, char c);

// fn_crawl.c
int		crawl(char *buf, char *str, t_token **head);

// fn_cmd_list.c
t_cmd	*cmd_lst_create(void);
int		cmd_lst_add_back(t_cmd **head, t_cmd *new);
int		cmd_lst_delete_list(t_cmd **head);

int		check_token_sequence(t_token *tokens);
t_cmd	*build_cmd_lst(t_token *token_lst);
int		add_argv(t_token *cur_token, t_cmd *cur_cmd);

#endif