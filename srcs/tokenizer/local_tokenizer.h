/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_tokenizer.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/08 13:11:18 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_TOKENIZER_H
# define LOCAL_TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "tokenizer.h"

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

#endif