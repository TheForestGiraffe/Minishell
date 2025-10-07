/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_token_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:37:21 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/07 13:15:33 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_tokenizer.h"

int	tls_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!new || !lst)
		return (-1);
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	cur = (*lst);
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	return (1);
}

void	tls_delete_list(t_token **head)
{
	t_token	*record;
	t_token	*cur;

	if (!head)
		return ;
	cur = *head;
	while (cur)
	{
		record = cur->next;
		free (cur->content);
		free (cur);
		cur = record;
	}
	*head = NULL;
}

t_token	*tls_create(char *str)
{
	t_token	*new;

	new = malloc (sizeof (t_token));
	if (!new)
		return (NULL);
	if (str)
		new->content = str;
	else
		new->content = NULL;
	new->next = NULL;
	new->type = UNSET;
	return (new);
}
