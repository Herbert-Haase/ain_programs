



LIBTYPE = a

STD = c++11
CC = g++
CXXFLAGS = -Wall -Wextra -Werror -Weffc++ -Wold-style-cast -std=$(STD) -pedantic

.PHONY: all

all:
ifeq ($(LIBTYPE), a)
	${CC} -shared benotung.o fachnote.o fachnoten_liste.o -o libaufgabe6.so
else 
	ar rs libaufgabe6.a benotung.o fachnote.o fachnoten_liste.o
endif

