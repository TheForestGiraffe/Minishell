/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_built_in_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:44:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/11/13 18:32:45 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "parser.h"

int	builtin_unset(t_exec_context *ctxt)
{
	(void)ctxt;
	printf("builtin_unset called\n");
	return (1);
}

int	builtin_env(t_exec_context *ctxt)
{
	(void)ctxt;
	printf("builtin_env called\n");
	return (1);
}
