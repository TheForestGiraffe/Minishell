/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/11 16:04:22 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "signals.h"
#include "parser.h"
#include "execute.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	handle_eof(t_exec_context	**exec_context)
{
	ft_putstr_fd("exit\n", 1);
	rl_clear_history();
	free(*exec_context);
	return (1);
}

static int	read_parse_and_execute(t_exec_context *exec_context)
{
	char			*line;

	line = readline("minishell$ ");
	if (!line)
		return (handle_eof(&exec_context));
	if (*line)
	{
		add_history(line);
		exec_context->cmd_lst = parse(line, exec_context);
		if (exec_context->cmd_lst)
			execute(exec_context);
	}
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec_context	exec_context;

	(void)argc;
	(void)argv;
	exec_context.envp = envp;
	exec_context.exit_state = 0;
	exec_context.cmd_lst = NULL;
	register_signals();
	while (1)
	{
		if (read_parse_and_execute(&exec_context))
			break ;
	}
	rl_clear_history();
	return (0);
}
