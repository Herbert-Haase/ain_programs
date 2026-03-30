// ExprLexer.java
public final class ExprLexer {
    public enum TokenType { NUMBER, PLUS, MINUS, MUL, DIV, LPAREN, RPAREN, WS, INVALIDCHAR }

    public static final class Token {
        public final TokenType type;
        public final String text;

        private Token(TokenType type, String text) {
            this.type = type; 
            this.text = text;
        }

        @Override
        public String toString() {
            return this.type + "(\"" + this.text + "\")";
        }
    }

    private char[] input;
    private int current;
    private char c;

    public ExprLexer(String input) {
        this.input = input.toCharArray();
        this.current = 0;
        this.c = this.input[0];
    }

    public Token nextToken() {
        while (this.c != '\000') {
            switch (this.c) {
            case ' ', '\t', '\r', '\n':
                ws();
                continue;
            case '+':
                consume();
                return new Token(TokenType.PLUS, "+");
            case '-':
                consume();
                return new Token(TokenType.MINUS, "-");
            case '*':
                consume();
                return new Token(TokenType.MUL, "*");
            case '/':
                consume();
                return new Token(TokenType.DIV, "/");
            case '(':
                consume();
                return new Token(TokenType.LPAREN, "(");
            case ')':
                consume();
                return new Token(TokenType.RPAREN, ")");
            case '0', '1', '2', '3', '4', '5', '6', '7', '8', '9':
                return number();
            default:
                return invalid();
            }
        }

        return null;
    }

    private Token number() {
        String text = "";
        do {
            text += this.c;
            consume();
        }  while (Character.isDigit(this.c));
        
        if (this.c == '.') {
            consume();
            if (!Character.isDigit(this.c)) {
                undo();
            } else {
                text += '.';
                do {
                    text += this.c;
                    consume();
                } while (Character.isDigit(this.c));
            }
        }

        return new Token(TokenType.NUMBER, text);
    }

    private void ws() {
        char c;
        while ((c = this.input[this.current]) == ' '
               || c == '\t' || c == '\r' || c == '\n') {
            consume();
        }
    }

    private Token invalid() {
        String text = String.valueOf(this.c);;
        consume();
        return new Token(TokenType.INVALIDCHAR, text);
    }

    private void consume() {
        ++this.current;
        if (this.current < this.input.length) {
            this.c = this.input[this.current];
        } else {
            this.c = '\000';
        }
    }
    
    private void undo() {
        --this.current;
        this.c = this.input[this.current];
    }
}

