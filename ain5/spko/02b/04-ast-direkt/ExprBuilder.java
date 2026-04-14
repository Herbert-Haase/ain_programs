// ExprBuilder.java
import org.antlr.v4.runtime.Token;
import java.util.Stack;

/**
 * Hilfsklasse zum Bauen des abstrakten Syntaxbaums (AST) direkt in ExprParser
 * ohne Umweg &uuml;ber den Ableitungsbaum (Parse Tree).
 */
final class ExprBuilder {
    private final Stack<Expr> stack = new Stack<Expr>();

    /**
     * Aufruf nur aus dem ExprParser.
     * @return AST root
     */
    Expr getAst() {
        return stack.pop();
    }

    /**
     * Aufruf nur aus den expr- und mutlExpr-Regeln von ExprParser.
     * @param op der Operator
     * @return this
     */
    ExprBuilder buildOperation(Token op) {
        Expr right = this.stack.pop();
        Expr left = this.stack.pop();
        this.stack.push(new Operation(left, op.getText(), right));
        return this;
    }

    /**
     * Aufruf nur aus der value-Regel von ExprParser.
     * @param s das Vorzeichen
     * @param n die Zahl
     * @return this
     */
    ExprBuilder buildValue(Token s, Token n) {
        String sign = (s == null) ? "" : s.getText();
        this.stack.push(new Value(sign + n.getText()));
        return this;
    }
}

