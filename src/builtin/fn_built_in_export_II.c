/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_export_II.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/25 15:40:10 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "local_builtin.h"
#include "local_execute.h"
#include "libft.h"

int	search_and_unset(char *content, char ***array, char *equal_pos)
{
	int		index;

	index = -1;
	if (equal_pos)
	{
		content = ft_substr (content, 0, equal_pos - content);
		if (!content)
			return (perror_int ("@search_and_unset:ft_substring: ", -1));
	}
	index = search_index (content, *array);
	if (index >= 0)
	{
		if (unset_this (index, array) == -1)
		{
			if (equal_pos)
				free (content);
			return (-1);
		}
	}
	if (equal_pos)
		free (content);
	return (1);
}

int	update_env_exports(char *content, t_exec_context *ctxt)
{
	char	*pos;

	pos = ft_strrchr (content, '=');
	if (pos)
	{
		if (search_and_unset (content, &ctxt->exports, pos) == -1)
			return (-1);
		if (search_and_unset (content, &ctxt->envp, pos) == -1)
			return (-1);
		ctxt->envp = append_array (content, ctxt->envp);
		if (!ctxt->envp)
			return (-1);
	}
	else
	{
		if (search_key_index (content, ctxt->envp) >= 0
			|| search_index (content, ctxt->exports) >= 0)
			return (1);
		ctxt->exports = append_array (content, ctxt->exports);
		if (!ctxt->exports)
			return (-1);
	}
	return (1);
}

/*

int	update_env_exports(char *content, t_exec_context *ctxt)
{
	int		index;
	char	*pos;
	char	*first_part;
	char	*temp;

	index = -1;
	pos = ft_strrchr (content, '=');
	first_part = NULL;

	// if it has =
	if (pos)
	{
		// search in exports and unset
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
			// search envp and unset
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
		// append to envp
		ctxt->envp = append_array (content, ctxt->envp);
		if (!ctxt->envp)
			return (-1);
	}
	// if it NO =
	else 
	{
		// search existing EXPORTs and unset
		index = search_index (content, ctxt->exports);
		if (index >= 0)
		{
			if (unset_this (index, &(ctxt->exports)) == -1)
				return (-1);
		}
		else
		{
			// you should search in env
				// if exist > return
			index = search_key_index (content, ctxt->envp);
			if (index >= 0)
				return (1);
		}
		// append to exports
		ctxt->exports = append_array (content, ctxt->exports);
		if (!ctxt->exports)
			return (-1);
	}
	return (1);
}

*/