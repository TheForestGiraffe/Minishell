/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_loop_pids.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/12 12:31:42 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	connect_pipes(int **fd_array, int pos, int count)
{
	if (!fd_array || !*fd_array)
		return (0);
	if (pos > 0)
	{
		if (dup2 (fd_array[pos - 1][0], STDIN_FILENO) == -1)
			return (perror_int ("@connect_pipes.dup2: ", -1));
	}
	if (pos + 1 <= count)
	{
		if (dup2 (fd_array[pos][1], STDOUT_FILENO) == -1)
			return (perror_int ("@connect_pipes.dup2: ", -1));
	}
	pos = 0;
	while (pos < count)
	{
		close (fd_array[pos][0]);
		close (fd_array[pos][1]);
		pos++;
	}
	return (1);
}

static int	run_on_child(int **fd_array, t_exec_context *exec_context,
						int i, int count)
{
	if (connect_pipes (fd_array, i, count - 1) == -1)
		return (-1);
	if (assign_input_output (exec_context->cmd_lst) == -1
		|| run_cmd (exec_context) == -1)
		exit (-1);
	exit (1);
}

int	loop_pids(int *process_id_arr, int **fd_array,
			int count, t_exec_context *exec_context)
{
	int	i;

	i = 0;
	while (i < count)
	{
		process_id_arr[i] = fork();
		if (process_id_arr[i] == -1)
		{
			perror ("@loop_pids.fork");
			return (-1);
		}
		if (process_id_arr[i] == 0)
			return (run_on_child (fd_array, exec_context, i, count));
		else
		{
			if (exec_context->cmd_lst->next)
				exec_context->cmd_lst = exec_context->cmd_lst->next;
			i++;
		}
	}
	return (1);
}
