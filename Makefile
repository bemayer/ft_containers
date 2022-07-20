NAME_DEBUG=	test_debug
NAME_STD=	test_std
NAME_FT=	test_ft
NAME_S=		test_subj
NAME_S_STD=	test_subj_std
TEST=		test.cpp
TEST_SUBJ=	test_subject.cpp
HPP=		map.hpp stack.hpp utility.hpp vector.hpp
HPP_B=		set.hpp
CXX=		c++
CXXFLAGS=	-Wall -Wextra -Werror -Wpedantic -std=c++98

all:		debug std ft subj subj_std

debug:		$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) -DDEBUG -o $(NAME_DEBUG)

std:		$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) -DSTD -o $(NAME_STD)

ft:			$(TEST) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST) -o $(NAME_FT)

subj:		$(TEST_SUBJ) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST_SUBJ) -o $(NAME_S)

subj_std:	$(TEST_SUBJ) $(HPP)
			$(CXX) $(CXXFLAGS) $(TEST_SUBJ) -DSTD -o $(NAME_S_STD)

bonus:		debug_b std_b ft_b

debug_b:	$(TEST) $(HPP) $(HPP_B)
			$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -DDEBUG -o $(NAME_DEBUG)

std_b:		$(TEST) $(HPP) $(HPP_B)
			$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -DSTD -o $(NAME_STD)

ft_b:		$(TEST) $(HPP) $(HPP_B)
			$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -o $(NAME_FT)

clean:
			rm -f $(NAME_DEBUG) $(NAME_STD) $(NAME_FT) $(NAME_S) $(NAME_S_STD)

re:			clean all
