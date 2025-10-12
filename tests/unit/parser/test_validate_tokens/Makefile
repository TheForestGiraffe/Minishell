# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/10 21:44:39 by pecavalc          #+#    #+#              #
#    Updated: 2025/10/12 17:39:35 by pecavalc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= test_check_token_sequence

ROOT_DIR 	= ../../../..
INCLUDE_DIR = $(ROOT_DIR)/include
PARSER_DIR 	= $(ROOT_DIR)/src/parser/

SRC			= test_check_token_sequence.c \
			  $(PARSER_DIR)/check_token_sequence.c \
			  $(PARSER_DIR)/crawl.c \
			  $(PARSER_DIR)/helpers.c \
			  $(PARSER_DIR)/token_lists.c \
			  $(PARSER_DIR)/tokenizer.c
			  
OBJ			= $(patsubst %.c, %.o, $(SRC))

LIBFT_DIR 			= $(ROOT_DIR)/libs/Libft-2.1.1
LIBFT_HEADER_DIR	= $(LIBFT_DIR)/include
LIBFT 				= $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR) -I$(PARSER_DIR) \
							   -I$(LIBFT_HEADER_DIR) 

all: $(NAME)

run: $(NAME)
	./$(NAME)

$(NAME): $(OBJ) $(LIBFT)
	cc $(CFLAGS) $^ -o $@

%.o: %.c
	cc $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

.PHONY: clean fclean re

clean:
	rm -f $(OBJ)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean 
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all
