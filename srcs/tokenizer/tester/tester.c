#include "tokenizer.h"

void	print_list(t_token *ls_token)
{
	if (ls_token == NULL)
	{
		printf ("list is NULL\n");
		return ;
	}
	while (ls_token->next)
	{
		printf (">%s<\n", ls_token->content);
		ls_token = ls_token->next;
	}
	printf (">%s<\n", ls_token->content);
	
}

int	main()
{
	t_token	*ls_token;

	// char *str = " ";
	// char *str = "";
	// char *str = "<<<<       ";
	// char *str = "<		< <<       ";
	char *str = "       the \"Weather\"   is | very co<ld but it is not cold>>er 'than' yester<<day";
	// char *str = "<  >";

	ls_token = tokenizer(str);
	if (!ls_token)
	{
		printf ("Couldn't create a list of tokens\n");
		return (-1);
	}

	print_list(ls_token);
	tls_delete_list (&ls_token);

}

// what error to return if string is empty?