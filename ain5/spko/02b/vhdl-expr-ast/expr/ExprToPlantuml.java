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
        // 1. Lexer & Parser initialisieren
        VHDLLexer lexer = new VHDLLexer(CharStreams.fromStream(System.in));
        VHDLParser parser = new VHDLParser(new CommonTokenStream(lexer));

        // 2. Parse Tree erzeugen (wir starten beim Statement oder der Expression)
        // Je nachdem, was du testen willst, z.B. parser.statement()
        ParseTree tree = parser.statement();

        if (parser.getNumberOfSyntaxErrors() > 0) {
            System.err.println("Syntaxfehler gefunden!");
            System.exit(1);
        }

        // 3. AST bauen
        VHDLExprBuilder builder = new VHDLExprBuilder();
        Expr ast = builder.build(tree);

        // 4. Test-Ausgabe
        System.out.println("Generierter AST:");
        System.out.println(new ExprPrinter().print(ast));
    }
}
