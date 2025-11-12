/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_builtin_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/12 11:59:42 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_builtin.h"
#include "libft.h"
#include "parser.h"

int	search_builtin_functions(t_cmd *cmd_lst, char **envp)
{
	int		len;
	char	*name;
	int		return_val;

	return_val = 0;
	name = cmd_lst->argv[0].content;
	len = 1024;
	if (ft_strncmp (name, "echo", len) == 0)
		return_val = builtin_echo (cmd_lst, envp);
	else if (ft_strncmp (name, "cd", len) == 0)
		return_val = builtin_cd (cmd_lst, envp);
	else if (ft_strncmp (name, "pwd", len) == 0)
		return_val = builtin_pwd (cmd_lst, envp);
	else if (ft_strncmp (name, "export", len) == 0)
		return_val = builtin_export (cmd_lst, envp);
	else if (ft_strncmp (name, "unset", len) == 0)
		return_val = builtin_unset (cmd_lst, envp);
	else if (ft_strncmp (name, "env", len) == 0)
		return_val = builtin_env (cmd_lst, envp);
	else if (ft_strncmp (name, "exit", len) == 0)
		return_val = builtin_exit (cmd_lst, envp);
	return (return_val);
}
