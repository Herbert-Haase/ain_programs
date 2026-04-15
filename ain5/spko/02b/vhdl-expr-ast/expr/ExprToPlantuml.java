package vhdl;

import vhdl.grammar.VHDLLexer;
import vhdl.grammar.VHDLParser;
import vhdl.ast.Expr;
import vhdl.ast.VHDLExprBuilder;
import vhdl.ast.ExprPrinter;
import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

public final class VHDLToAst {
    public static void main(String[] args) throws Exception {

        VHDLLexer lexer = new VHDLLexer(CharStreams.fromStream(System.in));
        VHDLParser parser = new VHDLParser(new CommonTokenStream(lexer));

        ParseTree tree = parser.statement();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            System.err.println("Syntaxfehler gefunden!");
            System.exit(1);
        }

        // AST bauen
        VHDLExprBuilder builder = new VHDLExprBuilder();
        Expr ast = builder.build(tree);

        // Test-Ausgabe
        System.out.println("Generierter AST:");
        System.out.println(new ExprPrinter().print(ast));
    }
}
