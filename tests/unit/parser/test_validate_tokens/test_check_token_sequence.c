/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_token_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:18:49 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/12 18:38:56 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"

void		test(char *description, char *input, int expected_out, int *res);
void 		print_result(int ret, char *description);
static int	is_line_valid(char *line);

int	main(void)
{
	int res;

	res = 1;
	
	// Pipes
	test("Pipe followed by WORD, even if not a command", "cat | outfile", 1, &res);
	test("Pipe preceeded by S_QT", "cat 'hello world' | echo", 1, &res);
	test("Pipe preceeded by D_QT", "cat \"hello world\" | echo", 1, &res);
	test("Pipe followed by S_QT", "ls | 'echo' $VAR", 1, &res);
	test("Pipe followed by D_QT", "ls | \"echo\" $VAR", 1, &res);
	test("Pipe followed by OUTPUT", "cat | >", 0, &res);
	test("Pipe followed by INPUT", "cat | <", 0, &res);
	test("Pipe followed by ROUTPUT", "cat | >>", 0, &res);
	test("Pipe followed by RINPUT", "cat | <<", 0, &res);
	test("Pipe at the end", "cat |    	", 0, &res);
	test("Pipe preceeded by OUTPUT", "cat > | echo", 0, &res);
	test("Pipe preceeded by INPUT", "cat < | echo", 0, &res);
	test("Pipe preceeded by ROUTPUT", "cat >> | echo", 0, &res);
	test("Pipe preceeded by RINPUT", "cat >> | echo", 0, &res);
	test("Pipe at the beginning","| echo $VAR", 0, &res);
	test("Pipe followed by |", "cat | echo || echo", 0, &res);
	test("Pipe followed by ||", "ls -l ||| wc -l", 0, &res);

	// Redirecions
	test("Redirection '>' followed by a WORD (target)", "ls -l > outfile", 1, &res);
	test("Redirection '>>'followed by a WORD (target)", "ls -l < outfile", 1, &res);
	test("Redirection '<' followed by a WORD (target)", "ls -l < outfile", 1, &res);
	test("Redirection '<<'followed by a WORD (target)", "ls -l < outfile", 1, &res);
	test("Redirection '>' followed by a S_QT (target)", "ls -l > 'outfile'", 1, &res);
	test("Redirection '>' followed by a D_QT (target)", "ls -l > \"outfile\" ", 1, &res);
	test("Redirection '<' followed by a S_QT (target)", "ls -l < 'outfile'", 1, &res);
	test("Redirection '<' followed by a D_QT (target)", "ls -l < \"outfile\" ", 1, &res);
	test("Redirection '>>' followed by a S_QT (target)", "ls -l >> 'outfile'", 1, &res);
	test("Redirection '>>' followed by a D_QT (target)", "ls -l >> \"outfile\" ", 1, &res);
	test("Redirection '<<' followed by a S_QT (target)", "ls -l << 'outfile'", 1, &res);
	test("Redirection '<<' followed by a D_QT (target)", "ls -l << \"outfile\" ", 1, &res);
	test("Redirection '>' at the end", "ls -l >", 0, &res);
	test("Redirection '<' at the end", "ls -l <", 0, &res);
	test("Redirection '>>'at the end", "ls -l >>", 0, &res);
	test("Redirection '<<'at the end", "ls -l <<", 0, &res);
	test("Redirection '>' followed by pipe", "ls -l >    |", 0, &res);
	test("Redirection '<' followed by pipe", "ls -l <  |", 0, &res);
	test("Redirection '>>' followed by pipe", "ls -l >>    |", 0, &res);
	test("Redirection '<<' followed by pipe", "ls -l <<    |", 0, &res);

	if (res == 1)
		printf("\ntest_check_token_sequence: [OK]\n");
	else
		printf("\ntest_check_token_sequence: [NOK]\n");
		
	return (0);
}

void test(char *description, char *input, int expected_out, int *res)
{
	int	partial_res;

	if (is_line_valid(input) == expected_out)
		partial_res = 1;
	else
		partial_res = 0;
	ft_printf("Test: %s\n", description);
	ft_printf("Input: %s\n", input);
	ft_printf("Expected output: %i\n", expected_out);
	print_result(partial_res, input);
	if (partial_res == 0)
		*res = 0;
}

static int	is_line_valid(char *line)
{
	t_token *token_lst;
	
	token_lst = tokenizer(line);
	if (!token_lst)
		return (-1);
	if (check_token_sequence(token_lst) == -1)
		return (0);
	tls_delete_list (&token_lst);
	return (1);
}

void	print_result(int ret, char *description)
{
	if (ret == 1)
		printf("%-30s [OK]\n", description);
	else if (ret == 0)
		printf("%-30s [NOK]\n", description);
	else if (ret == -1)
		{}
	else
		printf("%s:	The test function must return either 0 or 1. The test failed.\n", description);
	printf("\n");
}