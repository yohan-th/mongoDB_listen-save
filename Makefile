#*****************************************************************************#
#   ___  ____  __    ____  __   ____  __     __   ____    Makefile            #
#  / __)(  __)(  )  (  __)/ _\ (  _ \(  )   / _\ (  _ \                       #
# ( (_ \ ) _)  )(    ) _)/    \ ) _ (/ (_/\/    \ ) _ (   Created by yohan    #
#  \___/(__)  (__)  (__) \_/\_/(____/\____/\_/\_/(____/   2/07/2019 11:34:42  #
#                                                                             #
#           Contact: yohan.thollet@gfi.fr                  Updated by yohan   #
#                                                         2/07/2019 16:39:42  #
#*****************************************************************************#

.PHONY : all clean re

CFLAGS = -Wall -Werror -Wextra
NAME = lecteur/lecteur

D_SRC = lecteur/src/
D_OBJ = lecteur/obj/

SRC = lecteur.c mq.c mongo.c
INC = -I lecteur/inc/libbson-1.0 -I lecteur/inc/libmongoc-1.0

OBJ = $(addprefix $(D_OBJ), $(SRC:.c=.o))

# Works with mongoc-dev

$(D_OBJ)%.o : $(D_SRC)%.c
	@mkdir -p $(D_OBJ)
	@gcc $(CFLAGS) -o $@ -c $< $(INC) -lmongoc-1.0 -lbson-1.0

all: $(NAME)

$(NAME) : $(OBJ)
	gcc $(CFLAGS) -o $(NAME) $(OBJ) -lrt $(INC) -lmongoc-1.0 -lbson-1.0 -lpthread -DLinux 

clean:
	rm -rf $(D_OBJ)
	rm -f $(NAME)

re: clean all
