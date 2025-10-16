/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 19:41:33 by kalhanaw          #+#    #+#             */
/*   Updated: 2025/10/16 15:56:24 by pecavalc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <stdbool.h>

typedef enum e_type
{
	UNSET = -1,
	WORD,
	PIPE,
	INPUT,
	OUTPUT,
	RINPUT,
	ROUTPUT,
	S_QT,
	D_QT
}	t_token_type;

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
	t_token_type	type;
}	t_token;

typedef struct s_cmd {
	t_token			*argv_lst;
	char			*infile;
	bool			is_infile_heredoc;
	char 			*outfile;
	bool			append;
	struct s_cmd	*next;
}	t_cmd;

t_cmd	*parse(char *line);

#endif
