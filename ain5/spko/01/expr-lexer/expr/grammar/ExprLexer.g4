// // ExprLexer.g4
// lexer grammar ExprLexer;
//
// Number: Digits ('.' Digits)?;
//
// PLUS:   '+';
// MINUS:  '-';
// MUL:    '*';
// DIV:    '/';
// LPAREN: '(';
// RPAREN: ')';
//
// WS:     [ \t\r\n]+ -> channel(HIDDEN);
//
// InvalidChar: .;
//
// fragment Digits: ([0-9])+;
// VHDL is case insensitive, which means that upper- and lowercase letters can be used interchangeably, and free formatting, which means that spaces and blank lines can be inserted freely. -- Fpga Prototyping By Vhdl Examples
// lexer grammar VHDLLexer;
lexer grammar ExprLexer;

options { caseInsensitive = true; }

COMMENT : '--' ~[\r\n]* -> skip;

LIBRARY : 'library';
USE     : 'use';
ENTITY  : 'entity';
IS      : 'is';
PORT    : 'port';
END     : 'end';
ARCHITECTURE : 'architecture';
SIGNAL  : 'signal';
BEGIN   : 'begin';

IN  : 'in';
OUT : 'out';
OF  : 'of';
ALL : 'all';

STD_LOGIC : 'std_logic';

AND : 'and';
OR  : 'or';
NOT : 'not';

ASSIGN : '<=';

LPAREN : '(';
RPAREN : ')';
COLON  : ':';
SEMI   : ';';
COMMA  : ',';
DOT    : '.';

ID : [a-zA-Z_][a-zA-Z_0-9]*;

WS : [ \t\r\n]+ -> skip;

