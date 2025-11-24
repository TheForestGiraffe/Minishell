/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_export_I.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/24 19:16:18 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <parser.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

static void	fill_temp(char **temp, char **envp, char **exports)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (envp[i])
	{
		temp[i] = envp [i];
		i ++;
	}
	if (!exports || !*exports)
		return ;
	while (exports[j])
	{
		temp[i] = exports[j];
		j ++;
		i ++;
	}
}

static int	print_exports(t_exec_context *ctxt)
{
	char	**temp;
	int		len;
	int	i;

	len = get_len_array (ctxt->envp) + get_len_array (ctxt->exports);
	temp = malloc (sizeof (char *) * (len + 1));
	if (!temp)
		return (perror_int ("@print_exports: ", -1));
	temp [len] = NULL;
	fill_temp (temp, ctxt->envp, ctxt->exports);
	quick_sort (temp, 0, len - 1);
	i = -1;
	while (++i < len)
		printf ("declare -x %s\n", temp[i]);
	free (temp);
	return (1);
}

int	search_index(char *str, char **envp)
{
	int		i;
	int		len;

	if (!envp)
		return (-1);
	i = 0;
	len = ft_strlen (str) + 1;
	while (envp[i])
	{
		if (ft_strncmp (str, envp[i], len) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-2);
}

static int	update_env_exports(char *content, t_exec_context *ctxt)
{
	int		index;
	char	*pos;
	char	*first_part;
	char	*temp;

	index = -1;
	pos = ft_strrchr (content, '=');
	first_part = NULL;
	if (pos)
	{
		temp = ft_substr (content, 0, pos - content);
		if (!temp)
			return (perror_int ("@update_env_export.temp:ft_substring: ", -1));
		index = search_index (temp, ctxt->exports);
		if (index >= 0)
		{
			free (temp);
			if (unset_this (index, &(ctxt->exports)) == -1)
				return (-1);
		}
		else
		{
			free (temp);
			first_part = ft_substr (content, 0, pos - content);
			if (!first_part)
				return (perror_int ("@update_env_export.ft_substring: ", -1));
			index = search_key_index (first_part, ctxt->envp);
			if (index >= 0)
			{
				if (unset_this (index, &(ctxt->envp)) == -1)
				{
					free (first_part);
					return (-1);
				}
			}
			free (first_part);
		}
		ctxt->envp = append_array (content, ctxt->envp);
		if (!ctxt->envp)
			return (-1);
	}
	else 
	{
		index = search_index (content, ctxt->exports);
		if (index >= 0)
		{
			if (unset_this (index, &(ctxt->exports)) == -1)
				return (-1);
		}
		ctxt->exports = append_array (content, ctxt->exports);
		if (!ctxt->exports)
			return (-1);
	}
	return (1);
}

int	builtin_export(t_exec_context *ctxt)
{
	t_token	*current_arg;
	
	if (!ctxt->cmd_lst->argv->next)
		return (print_exports (ctxt));
	current_arg = ctxt->cmd_lst->argv->next;
	while (current_arg)
	{
		if (!is_valid (current_arg->content))
		{
			printf ("@export: `%s': not a valid identifier\n", current_arg->content);
			current_arg = current_arg->next;
			continue;
		}
		if (update_env_exports (current_arg->content, ctxt) == -1)
			return (-1);
		current_arg = current_arg->next;
	}
	return (1);
}
