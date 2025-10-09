# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 15:25:57 by pecavalc          #+#    #+#              #
#    Updated: 2025/10/09 17:20:57 by pecavalc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRCS_DIR = srcs
OBJS_DIR = objs

SRCS = $(addprefix $(SRCS_DIR)/, minishell.c \
								 signals.c)
OBJS = $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

HEADER_DIR = include
HEADER = $(HEADER_DIR)/minishell.h

# Parser
PARSER_SRCS_DIR = srcs/parser
PARSER_SRCS = $(addprefix $(PARSER_SRCS_DIR)/, fn_crawl.c \
											   fn_helpers.c \
											   fn_token_lists.c \
											   tokenizer.c)

PARSER_OBJS_DIR = objs/parser
PARSER_OBJS = $(patsubst $(PARSER_SRCS_DIR)/%.c, \
				$(PARSER_OBJS_DIR)/%.o, $(PARSER_SRCS))

PUB_PARSER_HEADER_DIR = include
LOCAL_PARSER_HEADER_DIR = $(PARSER_SRCS_DIR)
PARSER_HEADERS = $(PUB_PARSER_HEADER_DIR)/parser.h \
				 $(LOCAL_PARSER_HEADER_DIR)/local_parser.h

# Directories of all objects above - only used to create obj folders
OBJS_DIRS = $(OBJS_DIR) $(PARSER_OBJS_DIR)

# Libft
LIBFT_DIR = libs/Libft-2.1.1
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

CFLAGS = -Wall -Wextra -Werror -I$(HEADER_DIR) \
							   -I$(LOCAL_PARSER_HEADER_DIR) \
							   -I$(LIBFT_HEADER_DIR)

all: $(OBJS_DIRS) $(NAME)

# Create all obj folders beforehand
$(OBJS_DIRS):
	mkdir -p $@

# Compile minishell
$(NAME): $(OBJS) $(PARSER_OBJS) $(LIBFT)
	cc $(CFLAGS) $(OBJS) $(PARSER_OBJS) $(LIBFT) -lreadline -o $(NAME)

# Build main objs in srcs
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADER)
	cc $(CFLAGS) -c $< -o $@

# Build parser objs 
$(PARSER_OBJS_DIR)/%.o: $(PARSER_SRCS_DIR)/%.c $(PARSER_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Trigger Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	rm -rf $(OBJS_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re clean fclean
