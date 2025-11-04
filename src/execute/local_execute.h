/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_execute.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:54:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/30 09:43:13 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_EXECUTE_H
# define LOCAL_EXECUTE_H

# include "minishell.h"
# include "execute.h" // check for later
# include "parser.h"

typedef struct s_cmd	t_cmd;

// fn_assign_input_output.c
int		assign_input_output(t_cmd *cmd_lst);

// fn_assign_input_output_utils.c
int		check_heredoc_onreturn(t_cmd *cmd_lst, int val);

// fn_run_cmd.c
int		run_cmd(t_cmd *cmd_lst, char **envp);

// fn_utils.c
void	*free_str_array(char **arr);

// fn_get_full_path.c
char	*get_full_path(t_cmd *cmd_lst, char **envp);

#endif
