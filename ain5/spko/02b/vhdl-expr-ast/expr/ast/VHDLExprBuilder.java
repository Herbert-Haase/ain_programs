package expr.ast;

import expr.grammar.VHDLParser;
import expr.grammar.VHDLParserBaseListener;
import org.antlr.v4.runtime.tree.ParseTree;
import org.antlr.v4.runtime.tree.ParseTreeWalker;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;

public class VHDLExprBuilder extends VHDLParserBaseListener {
    private final Stack<Expr> stack = new Stack<>();
    private final List<Expr> assignments = new ArrayList<>();

    public Expr build(ParseTree tree) {
        new ParseTreeWalker().walk(this, tree);
        // Falls mehrere Statements gefunden wurden, geben wir eine Liste/Operation zurück
        // oder einfach das letzte gefundene Statement für den Plot.
        return assignments.isEmpty() ? null : assignments.get(assignments.size() - 1);
    }

    @Override
    public void exitPrimary(VHDLParser.PrimaryContext ctx) {
        if (ctx.ID() != null) {
            this.stack.push(new Id(ctx.ID().getText()));
        }
    }

    @Override
    public void exitNotExpr(VHDLParser.NotExprContext ctx) {
        if (ctx.NOT() != null) {
            Expr child = this.stack.pop();
            this.stack.push(new Not(child));
        }
    }

    @Override
    public void exitAndExpr(VHDLParser.AndExprContext ctx) {
        int count = ctx.notExpr().size();
        if (count > 1) buildLeftAssociativeTree("AND", count);
    }

    @Override
    public void exitOrExpr(VHDLParser.OrExprContext ctx) {
        int count = ctx.andExpr().size();
        if (count > 1) buildLeftAssociativeTree("OR", count);
    }
    
    @Override
    public void exitStatement(VHDLParser.StatementContext ctx) {
        Expr rhs = this.stack.pop();
        String targetId = ctx.ID().getText();
        assignments.add(new Assignment(targetId, rhs));
    }

    private void buildLeftAssociativeTree(String operator, int count) {
        List<Expr> nodes = new ArrayList<>();
        for (int i = 0; i < count; i++) nodes.add(this.stack.pop());
        Collections.reverse(nodes);
        Expr result = nodes.get(0);
        for (int i = 1; i < count; i++) {
            result = new Operation(result, operator, nodes.get(i));
        }
        this.stack.push(result);
    }
}
