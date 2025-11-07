/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:55:08 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/07 11:02:25 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "local_execute.h"

static int	cmd_lst_count(t_cmd *cmd_lst);

int	execute(t_cmd *cmd_lst, char **envp)
{
	int	pipe_count;

	pipe_count = cmd_lst_count (cmd_lst) - 1;
	if (pipe_count == 0) 
	{
		if (assign_input_output (cmd_lst) == -1
			|| run_cmd (cmd_lst, envp) == -1)
			return (-1);
		return (1);
	}
	return (0);
}

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
/*

TODO:

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
*/