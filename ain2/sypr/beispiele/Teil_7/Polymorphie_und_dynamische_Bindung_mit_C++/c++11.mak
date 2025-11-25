#
# c++11.mak
#
# Autor: H.Drachenfels
# erstellt am: 25.6.2015
#

CXX = g++
CXXFLAGS = -g -W -Wall -std=c++11

TARGET = DateClient-11

OBJECTS = \
  $(TARGET).o \
  CurrentDate.o \
  FixedDate.o

.PHONY: all clean

all: $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

DateClient.o: DateClient.cpp CurrentDate.h Date.h FixedDate.h
CurrentDate.o: CurrentDate.cpp CurrentDate.h Date.h
FixedDate.o: FixedDate.cpp FixedDate.h Date.h

