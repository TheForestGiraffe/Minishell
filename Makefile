# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pecavalc <pecavalc@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/07 15:25:57 by pecavalc          #+#    #+#              #
#    Updated: 2025/10/12 17:36:43 by pecavalc         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell 

SRC_DIR = src
OBJ_DIR = obj

SRC = $(addprefix $(SRC_DIR)/, minishell.c \
							   signals.c)
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

HEADER_DIR = include
HEADER = $(HEADER_DIR)/minishell.h

# Parser
PARSER_SRC_DIR = src/parser
PARSER_SRC = $(addprefix $(PARSER_SRC_DIR)/, crawl.c \
											 helpers.c \
											 token_lists.c \
											 check_token_sequence.c \
											 parse.c \
											 tokenizer.c)

PARSER_OBJ_DIR = obj/parser
PARSER_OBJ = $(patsubst $(PARSER_SRC_DIR)/%.c, \
				$(PARSER_OBJ_DIR)/%.o, $(PARSER_SRC))

PUB_PARSER_HEADER_DIR = include
LOCAL_PARSER_HEADER_DIR = $(PARSER_SRC_DIR)
PARSER_HEADERS = $(PUB_PARSER_HEADER_DIR)/parser.h \
				 $(LOCAL_PARSER_HEADER_DIR)/local_parser.h

# Directories of all objects above - only used to create obj folders
OBJ_DIRS = $(OBJ_DIR) $(PARSER_OBJ_DIR)

# Libft
LIBFT_DIR = libs/Libft-2.1.1
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

# For Mac OS compatibility
READLINE_PATH := $(shell brew --prefix readline)
LDFLAGS = -L$(READLINE_PATH)/lib -lreadline -lhistory
CPPFLAGS = -I$(READLINE_PATH)/include

CFLAGS = -Wall -Wextra -Werror -I$(HEADER_DIR) \
							   -I$(LOCAL_PARSER_HEADER_DIR) \
							   -I$(LIBFT_HEADER_DIR)

all: $(OBJ_DIRS) $(NAME)

# Create all obj folders beforehand
$(OBJ_DIRS):
	mkdir -p $@

# Compile minishell
$(NAME): $(OBJ) $(PARSER_OBJ) $(LIBFT)
	cc $(CFLAGS) $(LDFLAGS) $(OBJ) $(PARSER_OBJ) $(LIBFT) $(LDFLAGS) -o $(NAME)

# Build main obj in src
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	cc $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Build parser obj 
$(PARSER_OBJ_DIR)/%.o: $(PARSER_SRC_DIR)/%.c $(PARSER_HEADERS)
	cc $(CFLAGS) -c $< -o $@

# Trigger Libft compilation
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all re clean fclean
