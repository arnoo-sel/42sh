##
## Makefile for mysh in /home/jartho_d/42sh/mysh
## 
## Made by adrien1 jarthon
## Login   <jartho_d@epitech.net>
## 
## Started on  Mon May  5 10:13:27 2008 adrien1 jarthon
## Last update Fri Jun 13 15:52:31 2008 arnaud sellier
##

SRC	=	echo.c \
		env.c \
		exit.c \
		env.c \
		42.c \
		jobs.c \
		setenv.c \
		unsetenv.c \
		cd.c \
		bindkey.c \
		history_aff.c \
		alias.c \
		unalias.c \
		set_var.c \
		unset_var.c \
		disp_alias_value.c
 
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
