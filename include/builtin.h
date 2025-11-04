/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/30 10:19:02 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdbool.h>
# include "execute.h"

typedef struct s_cmd	t_cmd;

int		search_builtin_functions(t_cmd *cmd_lst, char **envp);
int		builtin_echo(t_cmd *cmd_lst, char **envp);
int		builtin_cd(t_cmd *cmd_lst, char **envp);
int		builtin_pwd(t_cmd *cmd_lst, char **envp);
int		builtin_export(t_cmd *cmd_lst, char **envp);
int		builtin_unset(t_cmd *cmd_lst, char **envp);
int		builtin_env(t_cmd *cmd_lst, char **envp);
int		builtin_exit(t_cmd *cmd_lst, char **envp);

#endif