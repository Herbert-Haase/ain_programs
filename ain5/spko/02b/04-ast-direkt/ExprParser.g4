// ExprParser.g4
parser grammar ExprParser;
options { tokenVocab=ExprLexer; }

@parser::members {
    private final ExprBuilder builder = new ExprBuilder();
    public final Expr build() {
        start();
        return builder.getAst();
    }
}

start
    : expr EOF
    ;

expr
    : multExpr
    | expr op=(PLUS | MINUS) multExpr { builder.buildOperation($op); }
    ;

multExpr
    : primary
    | multExpr op=(MUL | DIV) primary { builder.buildOperation($op); }
    ;

primary
    : LPAREN expr RPAREN
    | value
    ;

value
    : s=(PLUS | MINUS)? n=Number { builder.buildValue($s, $n); }
    ;
