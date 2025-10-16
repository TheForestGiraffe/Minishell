/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_cmd_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/16 11:25:14 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

t_cmd	*cmd_lst_create(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
	{
		perror("@cmd_lst_create:");
		return (NULL);
	}
	new->argv = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->append = false;
	new->next = NULL;
	return (new);
}
int cmd_lst_add_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*cur;

	if (!head || !new)
	{
		ft_putstr_fd("@cmd_lst_add_back: NULL input parameter", 2);
		return (-1);
	}
	if (!(*head))
	{
		*head = new;
		return (1);
	}
	cur = *head;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
	new->next = NULL;
	return (1);
}

int	cmd_lst_delete_list(t_cmd **head)
{
	int		i;
	t_cmd	*cur;
	t_cmd 	*next;

	if (!head || !*head)
	{
		ft_putstr_fd("@cmd_lst_delete_list: NULL input", 2);
		return (-1);
	}
	cur = *head;
	while (cur)
	{
		next = cur->next;
		free_argv(cur);
		free(cur->infile);
		free(cur->outfile);
		free(cur);
		cur = next;
	}
	*head = NULL;
	return (1);
}
void	free_argv(t_cmd *cur)
{
	int i;
	
	i = 0;
	if (cur->argv)
	{
		while (cur->argv[i])
			free(cur->argv[i++]);
		free(cur->argv);
	}
}
