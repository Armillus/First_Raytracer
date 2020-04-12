##
## EPITECH PROJECT, 2018
## makefile
## File description:
## makefile
##

NAME	=	raytracer

CXX	=	g++ -g3 -g

SRCS	=	src/main.cpp

OBJS	=	$(SRCS:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra -std=c++17 -pedantic -Ofast -pipe

LDFLAGS 	= 	-lsfml-window -lsfml-graphics -lsfml-system

#tests_run:
#	cd tests && $(MAKE)

all:	$(NAME)

$(NAME): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
