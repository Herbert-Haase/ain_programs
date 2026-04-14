// ExprParser.g4
parser grammar ExprParser;
options { tokenVocab=ExprLexer; }

@parser::members {
    public final ExprBuilder builder = new ExprBuilder();
    public final Expr build() {
        start();
        return builder.getAst();
    }
}

start
    : expr EOF
    ;

expr
    : multExpr (op=(PLUS | MINUS) multExpr { builder.buildOperation($op); })*
    ;

multExpr
    : primary (op=(MUL | DIV) primary { builder.buildOperation($op); })*
    ;

primary
    : LPAREN expr RPAREN
    | value
    ;

value
    : s=(PLUS | MINUS)? n=Number { builder.buildValue($s, $n); }
    ;
