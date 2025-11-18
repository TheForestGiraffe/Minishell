/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/18 17:52:00 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_BUILTIN_H
# define LOCAL_BUILTIN_H

# include "types.h"

int		builtin_echo(t_exec_context *ctxt);
int		builtin_cd(t_exec_context *ctxt);
int		update_env(char *cur_wd, char **envp);
int		builtin_pwd(t_exec_context *ctxt);
int		builtin_export(t_exec_context *ctxt);
int		builtin_unset(t_exec_context *ctxt);
int		builtin_env(t_exec_context *ctxt);
int		builtin_exit(t_exec_context *ctxt);

// fn_built_in_unset_II.c
int		unset_this(int index, char ***envp);

#endif