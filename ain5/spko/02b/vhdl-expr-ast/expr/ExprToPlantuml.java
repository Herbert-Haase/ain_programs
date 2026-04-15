// ExprToPlantuml.java
package expr;

import expr.grammar.VHDLLexer;
import expr.grammar.VHDLParser;
import expr.ast.Expr;
import expr.ast.VHDLExprBuilder;
import expr.ast.ExprPlotter;
import expr.ast.ExprPrinter;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import java.util.Arrays;
import java.util.List;

public final class ExprToPlantuml {
    private ExprToPlantuml() { }

    public static void main(String[] args) throws Exception {
        // CLI-Argumente parsen
        List<String> argList = Arrays.asList(args);
        boolean showTokens = argList.contains("--tokens");
        boolean showTree   = argList.contains("--tree");
        boolean showAst    = argList.contains("--ast");

        VHDLLexer lexer = new VHDLLexer(CharStreams.fromStream(System.in));
        CommonTokenStream tokens = new CommonTokenStream(lexer);

        // Optional: Lexer Tokens ausgeben (geht nach stderr)
        if (showTokens) {
            tokens.fill();
            System.err.println("=== TOKENS ===");
            for (org.antlr.v4.runtime.Token t : tokens.getTokens()) {
                String name = VHDLLexer.VOCABULARY.getSymbolicName(t.getType());
                System.err.printf("[%s: '%s'] ", name, t.getText().replace("\n", "\\n"));
            }
            System.err.println("\n");
            lexer.reset();
        }

        VHDLParser parser = new VHDLParser(tokens);
        ParseTree tree = parser.start();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            System.err.printf("%d error(s) detected%n", parser.getNumberOfSyntaxErrors());
            System.exit(1);
        }

        // Optional: LISP-Parse-Tree ausgeben (geht nach stderr)
        if (showTree) {
            System.err.println("=== PARSE TREE ===");
            System.err.println(tree.toStringTree(parser));
            System.err.println();
        }

        VHDLExprBuilder builder = new VHDLExprBuilder();
        Expr ast = builder.build(tree);

        // Optional: Textuellen AST ausgeben (geht nach stderr)
        if (showAst) {
            System.err.println("=== AST TEXT ===");
            System.err.println(new ExprPrinter().print(ast));
            System.err.println();
        }

        // Standard-Verhalten: PlantUML Code (geht immer nach stdout)
        if (ast != null) {
            System.out.print(new ExprPlotter().plot(ast));
        }
    }
}
