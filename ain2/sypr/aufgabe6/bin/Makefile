STD = c++11
CC = g++
CXXFLAGS = -Wall -Wextra -Werror -Weffc++ -Wold-style-cast -std=$(STD) -pedantic
RM = rm -f

TARGET = notenspiegel
SOURCES = $(TARGET).cpp
OBJECTS = $(SOURCES:.cpp=.o)
HEADERS = $(SOURCES:.cpp=.h)
LIBNAME = aufgabe6
LIBTYPE = a

ifeq ($(LIBTYPE), so)
	CXXFLAGS += -fPIC
endif

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -L../lib -l$(LIBNAME) -o $(TARGET)


clean:
	$(RM) $(TARGET)

%.o: %.cpp
	$(CC) -c -I../lib $(CXXFLAGS) $< -o $@

