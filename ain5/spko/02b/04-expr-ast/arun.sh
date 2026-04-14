#!/bin/sh
plantuml=plantuml-1.2025.2.jar
example=${1##*/}
example=${example%.*}

cmd="java -cp ExprAst.jar expr.ExprToPlantuml < $1"
echo $cmd
eval $cmd
cmd="java -cp ExprAst.jar expr.ExprToPlantuml < $1 | java -jar $plantuml -pipe -tsvg > ${example}-ast.svg"
echo $cmd
eval $cmd
