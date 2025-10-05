# ifndef TOKENIZER_H
#	define TOKENIZER_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"

typedef struct	s_token
{
	char			*content;
	struct s_token	*next;
}	t_token;


t_token	*tokenizer(char *str);

// fn_tocken_lists
int		tls_add_back(t_token **lst, t_token *new);
void	tls_delete_list(t_token **head);
t_token	*tls_create(char *str);

// fn_helpers
int		fn_is_space(char c);
int		fn_is_res(char c);

#endif