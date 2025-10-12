/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_token_sequence.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 21:18:49 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/12 19:19:46 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"

void		test(char *description, char *input, int expected_out, int *res);
void		print_result(int res, char *description);
static int	is_line_valid(char *line);

int	main(void)
{
	int	res;

	res = 1;
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
	test("Pipe at the beginning", "| echo $VAR", 0, &res);
	test("Pipe followed by |", "cat | echo || echo", 0, &res);
	test("Pipe followed by ||", "ls -l ||| wc -l", 0, &res);
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
	else if (res == 0)
		printf("\ntest_check_token_sequence: [NOK]\n");
	else if (res == -1)
		printf("\ntest_check_token_sequence: Error\n");
	return (0);
}

void	test(char *description, char *input, int expected_out, int *res)
{
	int	ret;

	ft_printf("Test: %s\n", description);
	ft_printf("Input: %s\n", input);
	ft_printf("Expected output: %i\n", expected_out);
	ret = is_line_valid(input);
	print_result(ret == expected_out, input);
	if (ret != expected_out)
		*res = 0;
	if (ret == -1)
		*res = -1;
}

static int	is_line_valid(char *line)
{
	t_token	*token_lst;

	token_lst = tokenizer(line);
	if (!token_lst)
		return (-1);
	if ((check_token_sequence(token_lst) == 0)
		|| check_token_sequence(token_lst) == -1)
	{
		tls_delete_list (&token_lst);
		return (0);
	}
	tls_delete_list (&token_lst);
	return (1);
}

void	print_result(int res, char *description)
{
	if (res == 1)
		printf("%-30s [OK]\n", description);
	else if (res == 0)
		printf("%-30s [NOK]\n", description);
	else if (res == -1)
		printf("%-30s [Function under test returned error (-1)\n", description);
	printf("\n");
}
