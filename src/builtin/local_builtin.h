/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_builtin.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/06 14:27:56 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_BUILTIN_H
# define LOCAL_BUILTIN_H

# include "parser.h"

int		builtin_echo(t_cmd *cmd_lst, char **envp);
int		builtin_cd(t_cmd *cmd_lst, char **envp);
int		builtin_pwd(t_cmd *cmd_lst, char **envp);
int		builtin_export(t_cmd *cmd_lst, char **envp);
int		builtin_unset(t_cmd *cmd_lst, char **envp);
int		builtin_env(t_cmd *cmd_lst, char **envp);
int		builtin_exit(t_cmd *cmd_lst, char **envp);

#endif