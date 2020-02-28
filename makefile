NAME= location

SRC_PATH= src
SRC_NAME= main.c rental.c	clien.c	cars.c\

HDR_PATH= includes
HDR_NAME= mini_project.h

OBJ_PATH= obj
OBJ_NAME= $(SRC_NAME:.c=.o)

SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

# **************************************************************************** #

CW=	gcc
CFLAGES= -Wall -Wextra -Werror

LD_FLAGS= -L$(LIB_PATH)
LD_LIBS= -l$(patsubst lib%.a,%, $(LIB))

HDR_FLAGS= -I$(HDR_PATH)

# **************************************************************************** #

all:  $(NAME) 

$(NAME):  $(OBJ)
	@$(CW) $(CFLAGS) $(OBJ) -o $@
	@ echo "\033[1;32m>> binary is ready ;)\033[0m"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR)
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CW) $(CFLAGS) $(HDR_FLAGS) -o $@ -c $<

clean:
	@rm -fr $(OBJ)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;33m>> Lem-in object files deleted.\033[0m" 

fclean:
	@rm -fr $(OBJ)
	@rm -fr $(NAME)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;33m>> Lem-in object files deleted.\033[0m" 
	@echo "\033[0;31m>> Lem-in binary deleted.\033[0m" 

re: fclean all
