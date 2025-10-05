#include "tokenizer.h"

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
		return (NULL); // perror
	if (str)
		new->content = str;
	else
		new->content = NULL;
	new->next = NULL;
	return (new);
}

