#!/bin/bash

STD="c++11"
CXX="g++ -c -g" #-fno-elide-constructors
CXXFLAGS="-Wall -Wextra -Werror -Weffc++ -Wold-style-cast -std=${STD} -pedantic"

for f in benotung.cpp fachnote.cpp fachnoten_liste.cpp ; do
  compile_command="${CXX} ${CXXFLAGS} ${f}"
  echo $compile_command
  eval $compile_command
  if [ $? -ne 0 ] ; then
    echo build failed
    exit 1
  fi
done

combine_command="ar rs libaufgabe6.a benotung.o fachnote.o fachnoten_liste.o"
echo $combine_command
eval $combine_command
if [ $? -ne 0 ] ; then
  echo combine to static lib failed
  exit 1
fi

echo libaufgabe6.a build successfully
