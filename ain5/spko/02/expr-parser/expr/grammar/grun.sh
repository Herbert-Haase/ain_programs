#!/bin/sh
t="java -cp Expr.jar org.antlr.v4.gui.TestRig grammar.Expr tokens -tokens $1 > ${1}.tokens"
echo $t
eval $t
gui="java -cp Expr.jar org.antlr.v4.gui.TestRig grammar.Expr start -gui $1"
echo $gui
eval $gui
