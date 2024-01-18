CFLAGS  =	-g -Wall -Wextra -Werror

CC      =	gcc

EXEC    =	miniProjet2p2

.PHONY  :   all clean

all     :	$(EXEC)

SRCS	=	biblioH.o \
			entreeSortieH.o \
			affichageH.o \
			libererH.o \
			utilsH.c \
			rechercheH.o \
			supprimeH.o \
			fusionH.o\
			mainH.o

miniProjet2p2 :	$(SRCS)
			$(CC) -o $@ $(CFLAGS) $^

%.o		:	%.c %.h
			$(CC)  $(GCC_FLAGS) -c  $<

clean	:
			rm -f *.o

fclean	:	clean
			rm $(EXEC)

re		:	clean all
