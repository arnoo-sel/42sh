##
## Makefile for 42sh in /home/farges_y/link/42sh/mysh/src/history
## 
## Made by yoam farges
## Login   <farges_y@epitech.net>
## 
## Started on  Fri May 30 15:00:02 2008 yoam farges
## Last update Fri Jun 13 15:53:18 2008 arnaud sellier
##

SRC	=	history.c \
		history_subs.c \
		file_history.c \
		get_subs.c \
		subs_search_hist.c \
		subs_str_hist.c \
		tools_subs_hist.c

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
