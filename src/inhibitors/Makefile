##
## Makefile<2> for 42sh in /u/epitech_2012/de-la-_o/cu/42sh_link/mysh/src/inhibitors
## 
## Made by jocelyn de-la-rosa
## Login   <de-la-_o@epitech.net>
## 
## Started on  Fri May 23 17:36:14 2008 jocelyn de-la-rosa
## Last update Fri Jun 13 15:55:07 2008 arnaud sellier
##

SRC	=	is_inhibited.c \
		str_to_wordtab_inhibitors.c \
		build_delimiters_tab.c \
		inhib_str.c

OBJ	= $(SRC:.c=.o)

INCLUDES_FILES	= ../../include/*.h

CC	= `sh ../../get_cc.sh`

CFLAGS	= -Wall -W -O3 $(INCLUDES)

INCLUDES	= -I../../include

LIBS	= -L../../lib/ -lmy-`uname -s`-`uname -m`

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

re: clean all
