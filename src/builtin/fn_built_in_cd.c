/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 14:26:12 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/16 23:13:43 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "parser.h"
#include "libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

// TODO: Fix NORM errors
// TODO: test with valgrind
// TODO: test

static int	set_envp(char *key, char *value, char **envp)
{
	int		i;
	int		len;
	char	*tmp;
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
	key_value_pair = ft_strjoin(key, "=");
	if (!key_value_pair)
	{
		ft_putstr_fd("@set_envp: 1st ft_strjoin failed", 2);
		return (-1);
	}
	tmp = key_value_pair;
	key_value_pair = ft_strjoin(key_value_pair, value);
	if (!key_value_pair)
	{
		ft_putstr_fd("@set_envp: 2nd ft_strjoin failed", 2);
		free(tmp);
		return (-1);
	}
	free(tmp);
	free(envp[i]);
	envp[i] = key_value_pair;
	return (1);	
}

static int	get_nr_args(t_token *argv)
{
	int i;
	
	if (!argv)
	{
		ft_putstr_fd("@fn_builtin_cd: count_args: NULL input\n", 2);
		return (-1);
	}
	i = 1;
	while (argv->next)
	{
		argv = argv->next;
		i++;
	}
	return (i);
}

int	builtin_cd(t_exec_context *exec_context)
{
	char	*cur_wd;
	char	*new_wd;
	int		nr_args;

	nr_args = get_nr_args(exec_context->cmd_lst->argv);
	if (nr_args == -1)
		return (-1);
	cur_wd = getcwd(NULL, 0);
	if (!cur_wd)
		perror("@builtin_cd.getcwd");
	
	// define target new_wd
	if (nr_args == 1)
	{
		new_wd = search_env("HOME", exec_context->envp);
		if (!new_wd || (ft_strncmp(new_wd, "", 1) == 0))
		{
			ft_putstr_fd("cd: HOME not set\n", 2);
			free(cur_wd);
			return (0);
		}
	}
	else if (nr_args == 2)
	{
		new_wd = ft_strdup(exec_context->cmd_lst->argv->next->content);
		if (!new_wd)
		{
			ft_putstr_fd("@builtin_cd: new_wd ft_strdup failed\n", 2);
			free(cur_wd);
			return (-1);
		}
	}
	else
	{
		ft_printf("bash: cd: too many arguments\n");
		free(cur_wd);
		return (0);
	}

	// Change directory to new_wd
	if (chdir(new_wd) == -1)
	{
		perror("@builtin_cd.chdir: chdir failed");
		free(cur_wd);
		free(new_wd);
		return (-1);
	}

	// Update PWD in envp
	if (set_envp("PWD", new_wd, exec_context->envp) == -1)
	{
		ft_putstr_fd("@builtin_cd: failed to set PWD", 2);
		free(cur_wd);
		free(new_wd);
		return (-1);
	}

	// Update OLDPWD in envp
	if (set_envp("OLDPWD", cur_wd, exec_context->envp) == -1)
	{
		ft_putstr_fd("@builtin_cd: failed to set OLDPWD", 2);
		free(cur_wd);
		free(new_wd);
		return (-1);
	}
	free(cur_wd);
	free(new_wd);
	if (exec_context->main_pid != getpid())
		exit(0);
	return (1);
}
