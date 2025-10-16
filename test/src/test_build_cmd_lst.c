/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_build_cmd_lst.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 13:10:00 by pecavalc          #+#    #+#             */
/*   Updated: 2025/10/16 16:30:00 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parser.h"
#include "libft.h"
#include <stdio.h>

void    test(char *description, char *line, char ***expected_cmds, int *res);
void    print_result(int ok, char *description);
static int  verify_cmd_list(t_cmd *cmd_list, char ***expected_cmds);
static int  compare_argv_lst(t_token *argv_lst, char **expected);

int main(void)
{
    int res = 1;

    char *pipeline1_cmd1[] = {"ls", "-l", NULL};
	char *pipeline1_cmd2[] = {"grep", "main", NULL};
	char *pipeline1_cmd3[] = {"wc", "-l", NULL};
	char **pipeline1[] = {pipeline1_cmd1, pipeline1_cmd2, pipeline1_cmd3, NULL};
    test("Pipeline: ls -l | grep main | \"wc\" -l", "ls -l | grep main | \"wc\" -l", pipeline1, &res);

    char *pipeline2_cmd1[] = {"echo", "hello", "world", NULL};
    char **pipeline2[] = {pipeline2_cmd1, NULL};
    test("Single command: echo hello world", "echo hello world", pipeline2, &res);

    char *pipeline3_cmd1[] = {"cat", NULL};
    char *pipeline3_cmd2[] = {"wc", "-l", NULL};
    char **pipeline3[] = {pipeline3_cmd1, pipeline3_cmd2, NULL};
    test("Pipeline with simple pipe: cat | wc -l", "cat | wc -l", pipeline3, &res);

    if (res == 1)
        printf("\ntest_cmd_list_pipeline: [OK]\n\n");
    else
        printf("\ntest_cmd_list_pipeline: [NOK]\n\n");

    return 0;
}

void test(char *description, char *line, char ***expected_cmds, int *res)
{
    t_cmd *cmd_list;

    cmd_list = parse(line);
    if (!cmd_list)
    {
        print_result(0, description);
        *res = 0;
        return;
    }

    if (verify_cmd_list(cmd_list, expected_cmds))
        print_result(1, description);
    else
    {
        print_result(0, description);
        *res = 0;
    }

    cmd_lst_delete_list(&cmd_list); // cleanup
}

static int verify_cmd_list(t_cmd *cmd_list, char ***expected_cmds)
{
    int     i = 0;
    t_cmd   *cur_cmd = cmd_list;

    while (cur_cmd && expected_cmds[i])
    {
        if (!compare_argv_lst(cur_cmd->argv_lst, expected_cmds[i]))
            return 0;
        cur_cmd = cur_cmd->next;
        i++;
    }
    // Check for mismatch in number of commands
    if (cur_cmd != NULL || expected_cmds[i] != NULL)
        return 0;
    return 1;
}

static int compare_argv_lst(t_token *argv_lst, char **expected)
{
    int     j = 0;
    t_token *cur = argv_lst;

    while (cur && expected[j])
    {
        if (ft_strncmp(cur->content, expected[j],
                       ft_strlen(expected[j]) + 1) != 0)
            return 0;
        cur = cur->next;
        j++;
    }
    // Mismatch in number of arguments?
    if (cur != NULL || expected[j] != NULL)
        return 0;
    return 1;
}

void print_result(int ok, char *description)
{
    if (ok)
        printf("%-50s [OK]\n", description);
    else
        printf("%-50s [NOK]\n", description);
}
