#!/bin/sh
testrig=org.antlr.v4.gui.TestRig
grammar=expr.grammar.Expr
example=${1##*/}
example=${example%.*}

cmd="java -cp Expr.jar $testrig $grammar start -gui $1"
echo $cmd
eval $cmd

cmd="sed -f pt-svg.sed antlr4_parse_tree.svg > ${example}-pt.svg"
echo $cmd
eval $cmd
