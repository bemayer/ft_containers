NAME_DEBUG   = test_debug
NAME_STD     = test_std
NAME_FT      = test_ft
NAME_S       = test_subj
NAME_S_STD   = test_subj_std
NAME_DEBUG_B = test_debug_bonus
NAME_STD_B   = test_std_bonus
NAME_FT_B    = test_ft_bonus

TEST         = test.cpp
TEST_SUBJ    = test_subject.cpp
HPP          = map.hpp stack.hpp utility.hpp vector.hpp
HPP_B        = set.hpp

CXX          = c++
CXXFLAGS     = -Wall -Wextra -Werror -Wpedantic -std=c++98

# Define phony targets
.PHONY: all test bonus clean re

# List of all executables
ALL_TARGETS  = $(NAME_DEBUG) $(NAME_STD) $(NAME_FT) $(NAME_S) $(NAME_S_STD)

all: $(ALL_TARGETS)

# Build rules for each executable
$(NAME_DEBUG): $(TEST) $(HPP)
	$(CXX) $(CXXFLAGS) $(TEST) -DDEBUG -o $(NAME_DEBUG)

$(NAME_STD): $(TEST) $(HPP)
	$(CXX) $(CXXFLAGS) $(TEST) -DSTD -o $(NAME_STD)

$(NAME_FT): $(TEST) $(HPP)
	$(CXX) $(CXXFLAGS) $(TEST) -o $(NAME_FT)

$(NAME_S): $(TEST_SUBJ) $(HPP)
	$(CXX) $(CXXFLAGS) $(TEST_SUBJ) -o $(NAME_S)

$(NAME_S_STD): $(TEST_SUBJ) $(HPP)
	$(CXX) $(CXXFLAGS) $(TEST_SUBJ) -DSTD -o $(NAME_S_STD)

# Bonus targets
bonus: $(NAME_DEBUG_B) $(NAME_STD_B) $(NAME_FT_B)

$(NAME_DEBUG_B): $(TEST) $(HPP) $(HPP_B)
	$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -DDEBUG -o $(NAME_DEBUG_B)

$(NAME_STD_B): $(TEST) $(HPP) $(HPP_B)
	$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -DSTD -o $(NAME_STD_B)

$(NAME_FT_B): $(TEST) $(HPP) $(HPP_B)
	$(CXX) $(CXXFLAGS) $(TEST) -DBONUS -o $(NAME_FT_B)

clean:
	rm -f $(ALL_TARGETS) $(NAME_DEBUG_B) $(NAME_STD_B) $(NAME_FT_B)

re: clean all

# Test all
test: all bonus
	./$(NAME_FT) > ft.log
	./$(NAME_STD) > std.log
	./$(NAME_S) 42 > subj.log
	./$(NAME_S_STD) 42 > subj_std.log
	./$(NAME_FT_B) > ft_bonus.log
	./$(NAME_STD_B) > std_bonus.log
	diff ft.log std.log
	diff subj.log subj_std.log
	diff ft_bonus.log std_bonus.log
