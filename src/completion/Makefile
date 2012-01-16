##
## Makefile<4> for 42sh in /home/jartho_d/42sh/mysh
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Mon Jun  9 10 50 53 2008 arnaud sellier
## Last update Fri Jun 13 15:52:53 2008 arnaud sellier
##

SRC	=	completion.c \
		complete_word.c \
		create_tab.c \
		read_for_completion.c \
		go_complete.c \
		aff_completion.c

OBJ	= $(SRC:.c=.o)

INCLUDES_FILES	= ../../include/*.h

CC	= `sh ../../get_cc.sh`

CFLAGS	= -Wall -W -O3 $(INCLUDES)

INCLUDES	= -I../../include

LIBS	= -L../../lib/ -lmy-`uname -s`-`uname -m` -lvector-`uname -s`-`uname -m`

all: $(OBJ)

$(OBJ): $(INCLUDES_FILES)

.c.o: *.h
	@echo -n "[36m[compi] "
	$(CC) $(CFLAGS) -c $<
	@echo -n "[0m"

clean:
	@echo -n "[31m[clean] "
	rm -f *~ *.o *#
	@echo -n "[0m"

fclean: clean

re: fclean all
