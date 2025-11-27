/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:04 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/15 23:43:30 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "local_builtin.h"
#include "types.h"
#include <stdlib.h>
#include <unistd.h>

static void	handle_exit_with_two_args(t_exec_context *exec_context)
{
	int		ret;
	long	number;

	ret = ft_strtol(exec_context->cmd_lst->argv->next->content, &number);
	if (ret == -1)
	{
		ft_printf("exit: %s: numeric argument required\n",
			exec_context->cmd_lst->argv->next->content);
		exit(255);
	}
	if (exec_context->main_pid == getpid())
		ft_printf("exit\n");
	exec_context->exit_state = (unsigned char)number;
	exit(exec_context->exit_state);
}

int	builtin_exit(t_exec_context *exec_context)
{
	int		nr_args;
	t_token	*cur_argv;

	if (!exec_context || !exec_context->cmd_lst
		|| !exec_context->cmd_lst->argv->content)
		exit(EXIT_FAILURE);
	cur_argv = exec_context->cmd_lst->argv;
	nr_args = 1;
	while (cur_argv->next)
	{
		cur_argv = cur_argv->next;
		nr_args++;
	}
	if (nr_args == 1)
	{
		if (exec_context->main_pid == getpid())
			ft_printf("exit\n");
		exit(exec_context->exit_state);
	}
	if (nr_args == 2)
		handle_exit_with_two_args(exec_context);
	ft_printf("exit: too many arguments\n");
	exit(1);
	return (1);
}
