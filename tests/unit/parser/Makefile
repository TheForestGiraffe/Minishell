# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 21:44:39 by pecavalc          #+#    #+#              #
#    Updated: 2025/10/12 17:38:43 by pecavalc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = run_parser_unit_tests

all: test_check_token_sequence \
	 test_tokenizer

test_check_token_sequence:
	@echo "\ntest_check_token_sequence:\n"
	@$(MAKE) -s -C test_check_token_sequence run

test_tokenizer:
	@echo "\ntest_tokenizer:\n"
	@$(MAKE) -s -C test_tokenizer run
	@echo "\n"

.PHONY: all clean fclean test_check_token_sequence test_tokenizer

clean:
	@$(MAKE) -s -C test_check_token_sequence clean
	@$(MAKE) -s -C test_tokenizer clean

fclean:
	@$(MAKE) -s -C test_check_token_sequence fclean
	@$(MAKE) -s -C test_tokenizer fclean

re: fclean all
