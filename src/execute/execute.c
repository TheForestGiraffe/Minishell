/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/11 16:13:25 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"
#include "parser.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

static int	cmd_lst_count(t_cmd *cmd_lst)
{
	int	len;

	if (!cmd_lst)
		return (0);
	len = 1;
	while (cmd_lst->next)
	{
		len ++;
		cmd_lst = cmd_lst->next;
	}
	return (len);
}

static void	close_all_fds(int **fd_array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		close (fd_array[i][0]);
		close (fd_array[i][1]);
		i++;
	}
}

static void	wait_all_pids(int *process_id_arr, int count, int *exit_state)
{
	int	i;

	i = 0;
	while (i < count)
	{
		waitpid (process_id_arr[i], exit_state, WUNTRACED);
		i ++;
	}
}

static void	cleanup_exec(int **fd_array, int **process_id_arr,
						t_exec_context *exec_context, int count)
{
	clear_fd_array (fd_array, count - 1);
	free (*process_id_arr);
	cmd_lst_delete_list (&exec_context->cmd_lst);
}

int	execute(t_exec_context *exec_context)
{
	int	*process_id_arr;
	int	**fd_array;
	int	count;

	count = cmd_lst_count (exec_context->cmd_lst);
	if (count == 0)
		return (1);
	process_id_arr = create_process_id_arr (&fd_array, count);
	if (!process_id_arr)
		return (-1);
	if (loop_pids (process_id_arr, fd_array, count, exec_context) == -1)
	{
		close_all_fds (fd_array, count - 1);
		cleanup_exec (fd_array, &process_id_arr, exec_context, count);
		return (-1);
	}
	close_all_fds (fd_array, count - 1);
	wait_all_pids (process_id_arr, count, &(exec_context->exit_state));
	cleanup_exec (fd_array, &process_id_arr, exec_context, count);
	return (1);
}
