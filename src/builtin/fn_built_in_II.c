/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/30 09:53:43 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"

int	builtin_unset(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_unset called\n");
	return (1);
}

int	builtin_env(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_env called\n");
	return (1);
}

int	builtin_exit(t_cmd *cmd_lst, char **envp)
{
	(void)cmd_lst;
	(void)envp;
	printf("builtin_exit called\n");
	return (1);
}
