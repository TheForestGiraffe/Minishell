/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/30 09:55:39 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_execute.h"

int	cmd_lst_count(t_cmd *cmd_lst)
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

int	execute (t_cmd *cmd_lst, char **envp)
{
	int	pipe_count;
	// int	**pid_arr;

	pipe_count = cmd_lst_count (cmd_lst) - 1;
	if (pipe_count == 0) 
	{
		if (assign_input_output (cmd_lst) == -1
		|| run_cmd (cmd_lst, envp) == -1)
		{
			// cmd_lst_clear (cmd_lst); FROM PEDRO
			return (-1);
		}
		// cmd_lst_clear (cmd_lst); FROM PEDRO
		return (1);
	}

	// create pipes array
	// pid_arr = malloc (sizeof (int *) * count);

	// fork ();
	// while loop
		// if on child fork
		// assign pid[i] to function
		// assign_input_output (cmd_lst) **overrides pipes**
		// run_cmd (cmd_lst)
		// on parent close pids
		// clean up
		// cmd_lst = cmd_lst.next;

	// wait for all functions
	// change exit_status 
	// clean up

	return (0);
}