/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/06 17:43:17 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef enum e_type
{
	UNSET = -1,
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	RINPUT,
	ROUTPUT,
	S_QT,
	D_QT
}	t_token_type;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

t_token	*tokenizer(char *str);

// fn_tocken_lists.c
int		tls_add_back(t_token **lst, t_token *new);
void	tls_delete_list(t_token **head);
t_token	*tls_create(char *str);

// fn_helpers.c
int		fn_is_space(char c);
int		fn_is_res(char c);
void	figure_type(t_token **current, char c);

// fn_crawl.c
int		crawl(char *buf, char *str, t_token **head);

#endif