CFLAGS  =	-g -Wall -Wextra -Werror

CC      =	gcc

EXEC    =	miniProjet2p1

.PHONY  :   all clean

all     :	$(EXEC)

SRCS	=	biblioLC.o \
			utils.o \
			entreeSortieLC.o \
			affichage.o \
			liberer.o \
			recherche.o \
			supprime.o \
			fusion.o\
			main.o 

miniProjet2p1 :	$(SRCS)
			$(CC) -o $@ $(CFLAGS) $^

%.o		:	%.c %.h
			$(CC)  $(GCC_FLAGS) -c  $<

clean	:
			rm -f *.o

fclean	:	clean
			rm $(EXEC)

re		:	clean all