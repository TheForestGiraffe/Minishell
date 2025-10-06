/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 11:54:30 by plima             #+#    #+#             */
/*   Updated: 2025/10/06 13:48:11 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft.h"
#include "signals.h"

int main(void)
{
    char    *line;

    setup_signals();
    while (1)
    {
        line = readline("Minishell$ ");
        if (!line)
        {
            ft_putstr_fd("exit\n", 1);
            break;
        }
        if (*line)
            add_history(line);
        printf("line: %s\n", line); // TODO: Remove
    }
    rl_clear_history();
    free(line);
    return (0);
}
