/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/17 14:57:54 by pecavalc         ###   ########.fr       */
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

#endif