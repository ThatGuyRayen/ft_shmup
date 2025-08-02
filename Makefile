# ************************************ #
#          ft_shmup Makefile           #
# *************************************#

# Compiler and flags
CXX       := c++
CXXFLAGS  := -Wall -Wextra -Werror -std=c++17
LDFLAGS   := -lncurses

# Directories
SRC_DIR   := src
INC_DIR   := include
OBJ_DIR   := obj

# Files
NAME      := ft_shmup
SRC       := $(wildcard $(SRC_DIR)/*.cpp)
OBJ       := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)



clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all


.PHONY: all clean fclean re
