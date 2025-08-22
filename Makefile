# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bdjoco <bdjoco@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/20 12:03:56 by miltavar          #+#    #+#              #
#    Updated: 2025/08/22 12:06:56 by bdjoco           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -Ilibs/libft/includes -Ilibs/ft_fprintf -Iincludes

MAKE = make -s -C

SRCS		= srcs/main.c

OBJS		= $(SRCS:.c=.o)

LIBFT_PATH	= libs/libft
LIBFT		= $(LIBFT_PATH)/libft.a

FT_FPRINTF_PATH	= libs/ft_fprintf
FT_FPRINTF		= $(FT_FPRINTF_PATH)/ft_fprintf.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	@$(MAKE) $(LIBFT_PATH)

$(FT_FPRINTF):
	@$(MAKE) $(FT_FPRINTF_PATH)

%.o: %.c includes/minishell.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@$(MAKE) $(LIBFT_PATH) clean
	@$(MAKE) $(FT_FPRINTF_PATH) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) $(LIBFT_PATH) fclean
	@$(MAKE) $(FT_FPRINTF_PATH) fclean

re: fclean all

.PHONY: all clean fclean re
