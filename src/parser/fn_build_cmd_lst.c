/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_build_cmd_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:57:06 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/15 15:13:45 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"

static int	add_word_to_argv(char *word, t_cmd *cur_cmd);

t_cmd	*build_cmd_lst(t_token *token_lst)
{
	t_cmd *cmd_lst;
	t_cmd *cur_cmd;

	if (!token_lst)
		return (NULL);
	cmd_lst = NULL;
	cur_cmd = cmd_lst_create();
	if (!cur_cmd)
		return (NULL);
	if (cmd_lst_add_back(&cmd_lst, cur_cmd) == -1)
		return (NULL);
	while (token_lst)
	{
		if (token_lst->type == WORD)
		{
			if (add_word_to_argv(token_lst->content, cur_cmd) == -1)
			{
				cmd_lst_delete_list(&cmd_lst);
				return (NULL);
			}
		}
		
		// To be continued here.
		// Also, review cmd_list.c

		token_lst = token_lst->next;
	}
	return (cmd_lst);
}

static int	add_word_to_argv(char *word, t_cmd *cur_cmd)
{
	int		i;
	char	**new_argv;

	if (!word || !cur_cmd)
		return (-1);
	if (!cur_cmd->argv)
	{
		cur_cmd->argv = malloc(sizeof(char *) * 2);
		if (!cur_cmd->argv)
			return (-1);
		cur_cmd->argv[1] = NULL;
		cur_cmd->argv[0] = ft_strdup(word);
		if (!cur_cmd->argv[0])
			return (-1);
		return (1);
	}
	i = 0;
	while (cur_cmd->argv[i])
		i++;
	new_argv = malloc(sizeof(char *) * (i + 2));
	if (!new_argv)
		return (-1);
	i = 0;
	while (cur_cmd->argv[i])
	{
		new_argv[i] = cur_cmd->argv[i];
		i++;
	}
	new_argv[i] = ft_strdup(word);
	if (!new_argv[i])
	{
		free(new_argv);
		return (-1);
	}
	new_argv[++i] = NULL;
	free(cur_cmd->argv);
	cur_cmd->argv = new_argv;
	return (1);
}
