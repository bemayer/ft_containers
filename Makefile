NAME=		test
SRC=		test.cpp
#SRC_SUBJ=	test_subject.cpp
CXX=		c++
CXXFLAGS=	-Wall -Wextra -Werror -std=c++98 -g

all:		$(NAME)
$(NAME):	$(SRC)
			$(CXX) $(CXXFLAGS) $(SRC) -o $(NAME)
clean:
			rm -f $(NAME)
fclean: 	clean
			rm -f $(NAME)
re:			fclean all