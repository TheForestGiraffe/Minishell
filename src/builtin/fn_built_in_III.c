/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_III.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:01 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/13 18:33:09 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <parser.h>

int	builtin_cd(t_exec_context *ctxt)
{
	(void)ctxt;
	printf("builtin_cd called\n");
	return (1);
}

int	builtin_pwd(t_exec_context *ctxt)
{
	char	*text;

	(void)ctxt;
	text = getcwd(NULL, 0);
	if (!text)
	{
		perror ("@pwd:");
		return (-1);
	}
	printf ("%s\n", text);
	free (text);
	return (1);
}

int	builtin_export(t_exec_context *ctxt)
{
	(void)ctxt;
	printf("builtin_export called\n");
	return (1);
}
