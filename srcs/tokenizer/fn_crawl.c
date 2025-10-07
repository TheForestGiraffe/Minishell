/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_crawl.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:36:45 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/07 13:15:22 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_tokenizer.h"

static int	handle_quotes(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	c;
	int		i;

	c = **p;
	(*p)++;
	i = 0;
	while (**p && **p != c)
		buf[i++] = *(*p)++;
	if (**p != c)
		return (-1);
	buf[i] = '\0';
	(*p)++;
	current = tls_create (ft_strdup (buf));
	if (!current)
		return (-1);
	figure_type (&current, c);
	return (tls_add_back (head, current));
}

static int	handle_redirects(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	*str;

	str = *p;
	buf[0] = str[0];
	buf[1] = str[1];
	buf[2] = '\0';
	(*p) += 2;
	current = tls_create (ft_strdup (buf));
	if (!current)
		return (-1);
	if (buf[0] == '>')
		current->type = ROUTPUT;
	else if (buf[0] == '<')
		current->type = RINPUT;
	return (tls_add_back (head, current));
}

static int	handle_special(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	*str;

	str = *p;
	if (*str == '"' || *str == '\'')
		return (handle_quotes (buf, p, head));
	else if ((str[0] == '<' && str[1] == '<')
		|| (str[0] == '>' && str[1] == '>'))
		return (handle_redirects (buf, p, head));
	else
	{
		buf[0] = *str;
		buf[1] = '\0';
		(*p)++;
		current = tls_create (ft_strdup (buf));
		if (!current)
			return (-1);
		figure_type (&current, buf[0]);
		return (tls_add_back (head, current));
	}
}

static int	handle_word(char *buf, char **str, t_token **head)
{
	int		i;
	t_token	*current;

	i = 0;
	while (!fn_is_space (**str) && !fn_is_res (**str) && **str)
	{
		buf[i] = **str;
		(*str)++;
		i ++;
	}
	buf[i] = '\0';
	current = tls_create (ft_strdup (buf));
	if (!current)
		return (-1);
	current->type = WORD;
	if (tls_add_back (head, current) == -1)
		return (-1);
	return (1);
}

int	crawl(char *buf, char *str, t_token **head)
{
	while (*str)
	{
		while (fn_is_space (*str))
			str ++;
		if (!*str)
			break ;
		if (fn_is_res (*str))
		{
			if (handle_special (buf, &str, head) == -1)
				return (-1);
		}
		else
		{
			if (handle_word(buf, &str, head) == -1)
				return (-1);
		}
	}
	return (1);
}
