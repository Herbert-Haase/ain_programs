#!/bin/bash

STD="c++11"
COMPILER="g++"
CXX="${COMPILER} -c -g" #-fno-elide-constructors
CXXFLAGS="-Wall -Wextra -Werror -Weffc++ -Wold-style-cast \
  -std=${STD} -pedantic -fPIC"

for f in benotung.cpp fachnote.cpp fachnoten_liste.cpp ; do
  compile_command="${CXX} ${CXXFLAGS} ${f}"
  echo $compile_command
  eval $compile_command
  if [ $? -ne 0 ] ; then
    echo build failed
    exit 1
  fi
done

combine_command="${COMPILER} -shared benotung.o fachnote.o fachnoten_liste.o \
  -o libaufgabe6.so"
echo $combine_command
eval $combine_command
if [ $? -ne 0 ] ; then
  echo combine to dynamic lib failed
  exit 1
fi

echo libaufgabe6.so build successfully
