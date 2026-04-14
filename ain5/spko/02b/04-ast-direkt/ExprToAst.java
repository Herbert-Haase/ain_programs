// ExprToAst.java
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;

public final class ExprToAst {
    private ExprToAst() { }

    public static void main(String[] args) throws Exception {
        ExprLexer lexer = new ExprLexer(CharStreams.fromStream(System.in));
        ExprParser parser = new ExprParser(new CommonTokenStream(lexer));
        parser.setBuildParseTree(false);

        Expr ast = parser.build();
        if (parser.getNumberOfSyntaxErrors() > 0) {
            System.err.printf("%d error(s) detected%n", parser.getNumberOfSyntaxErrors());
            System.exit(1);
        }

        System.out.printf("Expr.toString() = \"%s\"%n", ast);
    }
}

