/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/11/23 17:23:28 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "signals.h"
#include "parser.h"
#include "execute.h"
#include "echoctl.h"
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>

static int	copy_env_line(char **envp, char **new_envp, size_t i)
{
	new_envp[i] = ft_strdup(envp[i]);
	if (!new_envp[i])
	{
		while (i > 0)
			free(new_envp[--i]);
		free(new_envp);
		perror("@copy_environment.ft_strdup");
		return (-1);
	}
	return (1);
}

static char	**copy_env(char **envp)
{
	char	**new_envp;
	size_t	i;
	size_t	length;

	i = 0;
	while (envp[i])
		i++;
	length = i;
	new_envp = (char **)malloc((length + 1) * sizeof(char *));
	if (!new_envp)
	{
		perror("@copy_environment.malloc");
		return (NULL);
	}
	i = 0;
	while (i < length)
	{
		if (copy_env_line(envp, new_envp, i) == -1)
			return (NULL);
		i++;
	}
	new_envp[i] = NULL;
	return (new_envp);
}

static int	read_parse_and_execute(t_exec_context *exec_context)
{
	char	*line;

	line = readline("minishell$ ");
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (1);
	}
	if (*line)
	{
		add_history(line);
		if (parse(line, exec_context) == 1)
		{
			if (exec_context->cmd_lst)
				execute(exec_context);
		}
	}
	free(line);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_exec_context	exec_context;

	register_signals();
	atexit(enable_ctrl_chars_printing);
	(void)argc;
	(void)argv;
	exec_context.envp = copy_env(envp);
	if (!exec_context.envp)
		return (-1);
	exec_context.exports = NULL;
	exec_context.exit_state = 0;
	exec_context.cmd_lst = NULL;
	exec_context.main_pid = getpid();
	while (1)
	{
		disable_ctrl_chars_printing();
		if (read_parse_and_execute(&exec_context))
			break ;
	}
	rl_clear_history();
	return (0);
}
