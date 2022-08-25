# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iomayr <iomayr@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/11 16:41:15 by iomayr            #+#    #+#              #
#    Updated: 2022/08/25 16:39:54 by iomayr           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror 

CC = gcc

SRC = lexer/expand_dollar_utiles.c lexer/join_word.c \
		lexer/quotes.c lexer/expand_dollar.c \
		lexer/lexer.c lexer/get_symbol.c \
		lexer/get_delimiter.c \
		syntax/syntax_error.c syntax/error_message.c \
		parse/parse.c parse/parse_utiles.c\
		env/get_env.c \
		shell/main.c \
		libft/libft1.c \

OBJ = ${SRC:%.c=%.o}

NAME = minishell

all : ${NAME}

${NAME} : ${OBJ} includes/minishell.h
	@${CC} ${CFLAGS} ${OBJ} -o ${NAME} -lreadline
	@echo "\033[1;32m##########COMPILED SUCCESSFULY##########\033[0m"


clean:
	@rm -rf ${OBJ}

fclean: clean
	@rm -rf ${NAME}
	@echo "\033[1;32m##########CLEANED SUCCESSFULY##########\033[0m"


re: fclean all