/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/07 10:57:38 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "signals.h"
#include "parser.h"
#include "execute.h"
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

static int	read_parse_and_execute(char **envp);

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	register_signals();
	while (1)
	{
		if (read_parse_and_execute(envp))
			break ;
	}
	rl_clear_history();
	return (0);
}

static int	read_parse_and_execute(char **envp)
{
	char	*line;
	t_cmd	*cmd_lst;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	if (*line)
	{
		add_history(line);
		cmd_lst = parse(line, envp);
		if (cmd_lst)
			execute(cmd_lst, envp);
	}
	free(line);
	return (0);
}
