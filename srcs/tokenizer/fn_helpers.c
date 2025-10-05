#include "tokenizer.h"

int	fn_is_space(char c)
{
	if (c == ' ' || (c >= 9 && c <= 12))
		return (1);
	else
		return (0);
}

int	fn_is_res(char c)
{
	if (c == '\'' || c == '\"' || c == '<'
		|| c == '>'|| c == '|')
		return (1);
	else
		return (0);
}
