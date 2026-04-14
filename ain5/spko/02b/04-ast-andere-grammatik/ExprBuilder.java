// ExprBuilder.java
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import java.util.Stack;

/*
 * Transformiert einen ParseTree in einen abstrakten Syntaxbaum (AST).
 * Abstraktion:
 * - Weglassen der primary-Knoten und damit auch der Klammer-Tokens
 * - Weglassen von expr- und multExpr-Knoten mit nur einem Kind-Knoten
 * - einheitliche Transformation von expr- und multExpr-Knoten
 *   mit drei oder mehr Kind-Knoten
 */
public final class ExprBuilder extends ExprParserBaseListener {
    private Stack<Expr> stack = new Stack<Expr>();

    public Expr build(ParseTree tree) {
        new ParseTreeWalker().walk(this, tree);
        return this.stack.pop();
    }

    @Override
    public void exitExpr(ExprParser.ExprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            // Operatoren von links nach rechsts berechnen
            var s = new Stack<Expr>();
            for (int i = 0; i < n - 2; i += 2) {
                s.push(this.stack.pop());
            }
            for (int i = 1; i < n; i += 2) {
                this.stack.push(s.pop()); // rhs
                buildOperation(ctx.getChild(i).getText());
            }
        }
    }

    @Override
    public void exitMultExpr(ExprParser.MultExprContext ctx) {
        int n = ctx.getChildCount();
        if (n > 1) {
            // Operatoren von links nach rechsts berechnen
            var s = new Stack<Expr>();
            for (int i = 0; i < n - 2; i += 2) {
                s.push(this.stack.pop());
            }
            for (int i = 1; i < n; i += 2) {
                this.stack.push(s.pop()); // rhs
                buildOperation(ctx.getChild(i).getText());
            }
        }
    }

    @Override
    public void exitValue(ExprParser.ValueContext ctx) {
        String sign =
            switch (ctx.getStart().getType()) {
            case ExprLexer.PLUS, ExprLexer.MINUS -> ctx.getStart().getText();
            default -> "";
            };
        buildValue(sign, ctx.Number().getText());
    }

    protected final void buildOperation(String operator) {
        Expr rhs = this.stack.pop();
        Expr lhs = this.stack.pop();
        this.stack.push(new Operation(lhs, operator, rhs));
    }

    protected final void buildValue(String sign, String number) {
        this.stack.push(new Value(sign + number));
    }
}

