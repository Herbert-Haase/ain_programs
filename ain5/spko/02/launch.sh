#!/bin/bash

export CLASSPATH=".:/usr/share/java/antlr-complete.jar:$CLASSPATH"
antlr4 VHDLLexer.g4 VHDLParser.g4
javac VHDL*.java
java org.antlr.v4.gui.TestRig VHDL startRule -gui beispiel_vhdl.vhd
