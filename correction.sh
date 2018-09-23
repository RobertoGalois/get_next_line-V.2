# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    correction.sh                                      :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robert0 <fripponsupersonique@42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/30 18:20:35 by robert0           #+#    #+#              #
#    Updated: 2018/09/23 22:47:54 by robert0          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#make -C libft/ fclean
#make -C libft/
#clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
#clang -Wall -Wextra -Werror -I libft/includes -o main.o -c main.c
#clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
clang -Wall -Wextra -Werror -I libft/includes -o get_next_line.o -c get_next_line.c
clang -I libft/includes -o main.o -c main.c
clang -o test_gnl main.o get_next_line.o -I libft/includes -L libft/ -lft
./test_gnl ./filesTest/fichier_test.txt
