// ExprBuilderSemantics.java
package expr.ast;
import expr.grammar.ExprLexer;
import expr.grammar.ExprParser;
import org.antlr.v4.runtime.Token;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import java.util.Stack;

/**
 * Erweitert ExprBuilder um statische Semantik:
 * - Value mit maximal 8 Ziffern
 */
public final class ExprBuilderSemantics extends ExprBuilder {
    private static final int MAX_DIGITS = 8;
    private static final String ERROR_MAX_DIGITS
        = "number of digits exceeds " + MAX_DIGITS;

    private int numberOfSemanticErrors;

    private void semanticError(Token t, String error) {
        this.numberOfSemanticErrors++;
        System.err.printf("line %d column %d: %s%n",
                          t.getLine(), t.getCharPositionInLine(), error);
    }

    public int getNumberOfSemanticErrors() {
        return this.numberOfSemanticErrors;
    }

    @Override
    public Expr build(ParseTree tree) {
        this.numberOfSemanticErrors = 0;
        return super.build(tree);
    }

    @Override
    public void exitValue(ExprParser.ValueContext ctx) {
        // statische Semantik: maximal 8 Ziffern im String
        String number = ctx.Number().getText();
        int n = number.indexOf('.') < 0 ?
                number.length() : number.length() - 1;
        if (n > MAX_DIGITS) {
            semanticError(ctx.Number().getSymbol(), ERROR_MAX_DIGITS);
            super.buildValue("", "NaN");
            return;
        }

        super.exitValue(ctx);
    }
}

