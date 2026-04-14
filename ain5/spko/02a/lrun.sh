#!/bin/sh
java -cp '../antlr-4.13.1-complete.jar:.' org.antlr.v4.gui.TestRig VHDL tokens -tokens "$1"
