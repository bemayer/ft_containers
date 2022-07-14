NAME_DEBUG=	test_debug
NAME_STD=	test_std
NAME_FT=	test_ft
NAME_SUBJ=	test_subj
TEST=		test.cpp
TEST_SUBJ=	test_subject.cpp
HPP=		map.hpp utility.hpp vector.hpp
CXX=		c++
CXXFLAGS=	-Wall -Wextra -Werror -std=c++98 -g

all:		debug

debug:		$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) $(HPP) -DDEBUG -o $(NAME_DEBUG)

std:		$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) $(HPP) -o $(NAME_STD)

ft:			$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) $(HPP) -DFT -o $(NAME_FT)

subject:	$(TEST_SUBJ) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST_SUBJ) -o $(NAME_SUBJ)

clean:
			rm -f $(NAME_DEBUG) $(NAME_STD) $(NAME_FT) $(NAME_SUBJ)

fclean: 	clean
			rm -f $(NAME_DEBUG) $(NAME_STD) $(NAME_FT) $(NAME_SUBJ)

re:			fclean all