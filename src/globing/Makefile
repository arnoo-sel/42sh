##
## Makefile<4> for 42sh in /home/jartho_d/42sh/mysh
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Fri May 23 17:05:18 2008 adrien1 jarthon
## Last update Fri Jun 13 15:53:03 2008 arnaud sellier
##

SRC	=	globing.c \
		match.c \
		tild.c \
		file_glob.c \
		pattern_sub.c \
		str.c

OBJ	= $(SRC:.c=.o)

INCLUDES_FILES	= ../../include/*.h

CC	= `sh ../../get_cc.sh`

CFLAGS	= -Wall -W -O3 $(INCLUDES)

INCLUDES	= -I../../include

LIBS	= -L../../lib/ -lmy-`uname -s`-`uname -m` -lvector-`uname -s`-`uname -m`

all: $(OBJ)

$(OBJ): $(INCLUDES_FILES)

test:	test.o
	$(CC) $(CFLAGS) -o test test.o $(OBJ) $(LIBS)

.c.o: *.h
	@echo -n "[36m[compi] "
	$(CC) $(CFLAGS) -c $<
	@echo -n "[0m"

clean:
	@echo -n "[31m[clean] "
	rm -f *~ *.o *#
	@echo -n "[0m"

re: fclean all
