/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 14:13:04 by pecavalc          #+#    #+#             */
/*   Updated: 2025/11/03 16:14:18 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	builtin_exit(int argc, char **argv, int last_status)
{
	long	user_exit_code;
	int		ret;

	if (argc == 1)
		exit(last_status);
	if (argc == 2)
	{
		ret = ft_strtol(argv[1], &user_exit_code);
		if (ret == -1)
		{
			ft_printf("exit: %s: numeric argument required\n", argv[1]);
			exit(2);
		}
		exit((unsigned char)user_exit_code);
	}
	if (argc > 2)
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	return (1);
}
