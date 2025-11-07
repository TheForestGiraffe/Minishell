/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_token_lists.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:37:21 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 10:16:30 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "local_parser.h"

int	tls_add_back(t_token **lst, t_token *new)
{
	t_token	*cur;

	if (!new || !lst)
	{
		printf ("@tls_add_back: NULL input");
		return (-1);
	}
	if (!(*lst))
	{
		*lst = new;
		return (1);
	}
	cur = (*lst);
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->next = NULL;
	return (1);
}

void	tls_delete_list(t_token **head)
{
	t_token	*record;
	t_token	*cur;

	if (!head)
	{
		printf ("@tls_delete_list: NULL input");
		return ;
	}
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
	{
		perror ("@tls_create:");
		return (NULL);
	}
	if (str)
		new->content = str;
	else
		new->content = NULL;
	new->next = NULL;
	new->type = UNSET;
	return (new);
}

int	add_buf_to_list(char *buf, t_token **head, t_token_type type)
{
	t_token	*current;

	current = tls_create (ft_strdup (buf));
	if (!current)
	{
		perror ("@add_buf_to_list:");
		return (-1);
	}
	current->type = type;
	if (tls_add_back (head, current) == -1)
		return (-1);
	return (1);
}
