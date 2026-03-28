fgrammar Calc;

// --- Parser Rules (Start with lowercase) ---
prog:   expr EOF ;                  // The entry point: an expression followed by End Of File

expr:   expr op=('*'|'/') expr      // Multiplication and Division
    |   expr op=('+'|'-') expr      // Addition and Subtraction
    |   INT                         // An integer
    |   '(' expr ')'                // Parentheses
    ;

// --- Lexer Rules (Start with uppercase) ---
INT :   [0-9]+ ;                    // Match integers
WS  :   [ \t\r\n]+ -> skip ;        // Match whitespace and tell ANTLR to ignore it
