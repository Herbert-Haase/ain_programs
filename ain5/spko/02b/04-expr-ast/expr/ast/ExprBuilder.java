// ExprBuilder.java
package expr.ast;
import expr.grammar.ExprLexer;
import expr.grammar.ExprParser;
import expr.grammar.ExprParserBaseListener;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import java.util.Stack;

/**
 * Transformiert einen ParseTree in einen abstrakten Syntaxbaum (AST).
 * Abstraktion:
 * - Weglassen der primary-Knoten und damit auch der Klammer-Tokens
 * - Weglassen von expr- und multExpr-Knoten mit nur einem Kind-Knoten
 * - einheitliche Transformation von expr- und multExpr-Knoten
 *   mit drei Kind-Knoten
 */
public class ExprBuilder extends ExprParserBaseListener {
    private final Stack<Expr> stack = new Stack<Expr>();

    public Expr build(ParseTree tree) {
        new ParseTreeWalker().walk(this, tree);
        return this.stack.pop();
    }

    @Override
    public void exitExpr(ExprParser.ExprContext ctx) {
        if (ctx.getChildCount() == 3) {
            buildOperation(ctx.getChild(1).getText());
        }
    }

    @Override
    public void exitMultExpr(ExprParser.MultExprContext ctx) {
        if (ctx.getChildCount() == 3) {
            buildOperation(ctx.getChild(1).getText());
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

