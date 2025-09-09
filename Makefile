# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miltavar <miltavar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 12:03:56 by miltavar          #+#    #+#              #
#    Updated: 2025/09/09 17:03:44 by miltavar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -g3 -Wall -Wextra -Werror -Ilibs/libft/includes -Ilibs/ft_fprintf -Iincludes
LDFLAGS		= -lreadline

MAKE = make -s -C

SRCS = srcs/main.c \
		srcs/environement/env.c \
		srcs/environement/env_utils.c \
		srcs/minisplit/mini_split.c \
		srcs/minisplit/split_size.c \
		srcs/minisplit/split_write.c \
		srcs/minisplit/split_utils.c \
		srcs/exec/exec.c \
		srcs/exec/exec_utils.c \
		srcs/exec/exec_utils2.c \
		srcs/exec/redir_utils.c \
		srcs/exec/redir.c \
		srcs/built-in/echo/echo.c \
		srcs/built-in/unset/unset.c \
		srcs/built-in/pwd/pwd.c \
		srcs/built-in/env/env.c \
		srcs/built-in/export/export.c \
		srcs/built-in/export/export_utils.c \
		srcs/built-in/cd/cd.c \
		srcs/readline/readline.c \
		srcs/readline/readline_utils.c \
		srcs/utils/lib_utils.c \
		srcs/built-in/exit/exit.c


BOLD = \e[1m
GRAY = \e[30m
GREEN = \e[32m
PURPLE = \e[35m
RESET = \e[0m

OBJS		= $(SRCS:.c=.o)

LIBFT_PATH	= libs/libft
LIBFT		= $(LIBFT_PATH)/libft.a

FT_FPRINTF_PATH	= libs/ft_fprintf
FT_FPRINTF		= $(FT_FPRINTF_PATH)/ft_fprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(FT_FPRINTF)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(FT_FPRINTF) $(LDFLAGS) -o $(NAME)
	@echo "⚜️​   $(BOLD)$(PURPLE)$(NAME)$(RESET) $(GREEN)est compilé$(RESET) ​⚜️​​"

$(LIBFT):
	@$(MAKE) $(LIBFT_PATH)

$(FT_FPRINTF):
	@$(MAKE) $(FT_FPRINTF_PATH)

%.o: %.c includes/minishell.h
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) $(LIBFT_PATH) clean
	@$(MAKE) $(FT_FPRINTF_PATH) clean
	@echo "$(GRAY)Nettoyage des$(RESET) $(BOLD)fichiers source de minishell$(RESET) $(GRAY)terminé$(RESET) 🚮"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) $(LIBFT_PATH) fclean
	@$(MAKE) $(FT_FPRINTF_PATH) fclean
	@echo "$(GRAY)Nettoyage de$(RESET) $(BOLD)$(NAME)$(RESET) $(GRAY)terminé$(RESET) 🚮"

#--------------------------------------------#
cook: all clean
	@echo "🍴 $(BOLD)$(PURPLE)On cook$(RESET) 🍴"
#--------------------------------------------#

re: fclean all

.PHONY: all clean fclean re
