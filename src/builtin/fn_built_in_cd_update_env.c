/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_cd_update_env.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:26:12 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/17 13:07:38 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

static int	assemble_key_value_pair(char **key_value_pair, char *key,
									char *value)
{
	char	*tmp;

	*key_value_pair = ft_strjoin(key, "=");
	if (!(*key_value_pair))
	{
		ft_putstr_fd("@set_envp: 1st ft_strjoin failed", 2);
		return (-1);
	}
	tmp = *key_value_pair;
	*key_value_pair = ft_strjoin(*key_value_pair, value);
	if (!(*key_value_pair))
	{
		ft_putstr_fd("@set_envp: 2nd ft_strjoin failed", 2);
		free(tmp);
		return (-1);
	}
	free(tmp);
	return (1);
}

static int	set_envp(char *key, char *value, char **envp)
{
	int		i;
	int		len;
	char	*key_value_pair;

	if (!key || !value || !envp)
	{
		ft_putstr_fd("@set_envp: NULL input", 2);
		return (-1);
	}
	len = ft_strlen (key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp (key, envp[i], len) == 0)
			break ;
		i++;
	}
	if (assemble_key_value_pair(&key_value_pair, key, value) == -1)
		return (-1);
	free(envp[i]);
	envp[i] = key_value_pair;
	return (1);
}

int	update_env(char *new_wd, char *cur_wd, char **envp)
{
	if (set_envp("PWD", new_wd, envp) == -1)
	{
		ft_putstr_fd("@builtin_cd: failed to set PWD\n", 2);
		free(cur_wd);
		free(new_wd);
		return (-1);
	}
	if (set_envp("OLDPWD", cur_wd, envp) == -1)
	{
		ft_putstr_fd("@builtin_cd: failed to set OLDPWD", 2);
		free(cur_wd);
		free(new_wd);
		return (-1);
	}
	return (1);
}
