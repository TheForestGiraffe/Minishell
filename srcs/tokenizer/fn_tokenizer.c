#include "tokenizer.h"

static int	set_buffer(char **buf, char *str)
{
	int	len;

	len = ft_strlen (str);
	*buf = malloc (sizeof (char) * (len + 1));
	if (!*buf)
		return (-1);
	return (1);
}

static int	handle_special(char *buf, char **p, t_token **head)
{
	t_token	*current;
	char	*str;

	str = *p;
	
	buf[0] = *str;
	buf[1] = '\0';
	if ((str[0] == '<' && str[1] == '<') ||
		(str[0] == '>' && str[1] == '>'))
	{
		buf[1] = str[1];
		buf[2] = '\0';
		(*p) ++;
	}
	current = tls_create (ft_strdup (buf));
	if (tls_add_back (head, current) == -1)
		return (-1); // print msg?
	(*p) ++;
	return (1);
}

static int	handle_word(char *buf, char **str, t_token **head)
{
	int	i;
	t_token *current;

	i = 0;
	while (!fn_is_space (**str) && !fn_is_res (**str) && **str)
	{
		buf[i] = **str;
		(*str) ++;
		i ++;
	}
	buf[i] = '\0';
	current = tls_create (ft_strdup (buf));
	if (tls_add_back (head, current) == -1)
		return (-1);
	return (1);
}

static int	crawl(char *buf, char *str, t_token **head)
{
	while (*str)
	{
		while (fn_is_space (*str))
			str ++;
		if (!*str)
			break;
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

t_token	*tokenizer(char *str)
{
	t_token	*head;
	char	*buf;

	head = NULL;
	if (!str || !*str)
		return (NULL);
	if (set_buffer (&buf, str) == -1)
		return (NULL);
	if (crawl(buf, str, &head) == -1)
	{
		free (buf);
		tls_delete_list (&head);
		return (NULL);
	}
	free (buf);
	return (head);
}