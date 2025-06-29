


STD = c++11
CC = g++
CXXFLAGS = -Wall -Wextra -Werror -Weffc++ -Wold-style-cast -std=$(STD) -pedantic
RM = rm -f

SOURCES = benotung.cpp fachnote.cpp fachnoten_liste.cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(SOURCES:.cpp=.h)
LIBNAME = libaufgabe6
LIBTYPE = a

ifeq ($(LIBTYPE), so)
	CXXFLAGS += -fPIC
endif

.PHONY: all clean

all:
	$(MAKE) $(LIBNAME).$(LIBTYPE)


clean:
	$(RM) $(LIBNAME).* $(OBJECTS) depend

depend: $(SOURCES) $(HEADERS)
	$(CC) $(CXXFLAGS) -MM $(SOURCES) > $@

$(LIBNAME).a: $(OBJECTS)
	ar rs $@ $^

$(LIBNAME).so: $(OBJECTS)
	${CC} -shared $^ -o $@



%.o: %.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

include depend
