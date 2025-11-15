/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:04 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/15 22:01:48 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "local_builtin.h"
#include "types.h"
#include <stdlib.h>

static void	handle_exit_with_one_arg(t_exec_context *exec_context)
{
	int		ret;

	ret = ft_strtol(exec_context->cmd_lst->argv->next->content,
			exec_context->exit_state);
	if (ret == -1)
	{
		ft_printf("exit: %s: numeric argument required\n",
			exec_context->cmd_lst->argv->next);
		exit(2);
	}
	ft_printf("exit\n");
	exit(exec_context->exit_state);
}

int	builtin_exit(t_exec_context *exec_context)
{
	int		nr_args;
	t_token	*cur_arg;

	if (!exec_context || !exec_context->cmd_lst)
		exit(EXIT_FAILURE);
	nr_args = 0;
	while (exec_context->cmd_lst->argv->next)
	{
		cur_arg = exec_context->cmd_lst->argv->next;
		nr_args++;
	}
	if (nr_args == 0 && (exec_context->main_pid == getpid()))
	{
		ft_printf("exit\n");
		exit(exec_context->exit_state);
	}
	if (nr_args == 1)
		handle_exit_with_one_arg(exec_context);
	ft_printf("exit: too many arguments\n");
	exit(1);
	return (1);
}
