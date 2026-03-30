// ExprToPlantuml.java
package expr;
import expr.grammar.ExprLexer;
import expr.grammar.ExprParser;
import expr.ast.Expr;
import expr.ast.ExprBuilder;
import expr.ast.ExprPlotter;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

public final class ExprToPlantuml {
    private ExprToPlantuml() { }

    public static void main(String[] args) throws Exception {
        ExprLexer lexer = new ExprLexer(CharStreams.fromStream(System.in));
        ExprParser parser = new ExprParser(new CommonTokenStream(lexer));
        ParseTree tree = parser.start();
        if (parser.getNumberOfSyntaxErrors() > 0) {
            System.err.printf(
                "%d error(s) detected%n", parser.getNumberOfSyntaxErrors());
            System.exit(1);
        }

        ExprBuilder builder = new ExprBuilder();
        Expr ast = builder.build(tree);
        System.out.print(new ExprPlotter().plot(ast));
    }
}

