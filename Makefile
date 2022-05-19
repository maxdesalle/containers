# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlazzare <mlazzare@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/06 09:20:39 by mlazzare          #+#    #+#              #
#    Updated: 2022/05/19 21:18:12 by mdesalle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CNT-FT = containers-ft
CNT-STL = containers-stl

CXX = c++
CXXFLAGS = -Wall -Werror -Wextra -std=c++98

SRCS			=	tests/main.cpp											

INC		=	src/map.hpp						\
			src/stack.hpp					\
			src/vector.hpp					\
			src/vector_iterator.hpp			\
			src/enable_if.hpp				\
			src/equal.hpp					\
			src/pair.hpp					\
			src/RBTree.hpp					\
			src/RBTree_iterator.hpp			\

all: $(CNT-FT) $(CNT-STL)

$(CNT-FT): $(SRCS) $(INC)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@

$(CNT-STL): $(SRCS) $(INC)
	$(CXX) $(CXXFLAGS) $(SRCS) -D STL=1 -o $@

clean: fclean

fclean:
	@rm -f $(CNT-FT)
	@rm -f $(CNT-STL)

re: fclean all

.PHONY: all clean re fclean
