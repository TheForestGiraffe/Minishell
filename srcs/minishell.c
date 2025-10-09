/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/10/09 17:26:41 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_list(t_token *ls_token)
{
	char *t_str[] = 
	{
	"WORD",
	"PIPE",
	"INPUT",
	"OUTPUT",
	"RINPUT",
	"ROUTPUT",
	"S_QT",
	"D_QT"
	};


	if (ls_token == NULL)
	{
		printf ("list is NULL\n");
		return ;
	}
	while (ls_token->next)
	{
		printf ("%-25s type:%s\n", ls_token->content, t_str[ls_token->type]);

		ls_token = ls_token->next;
	}
	printf ("%-25s type:%s\n", ls_token->content, t_str[ls_token->type]);

}


int	main(void)
{
	char	*line;
	t_token *tokens;

	register_signals();
	while (1)
	{
		line = readline("Minishell$ ");
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (*line)
		{
			add_history(line);
			tokens = tokenizer(line);
			if (!tokens)
				continue ;
			// tester
			print_list(tokens);
			// tls_delete_list (&ls_token);
		}
	}
	rl_clear_history();
	free(line);
	return (0);
}
